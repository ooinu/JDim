// ライセンス: GPL2

//#define _DEBUG
#include "jddebug.h"

#include "playsound.h"

#ifdef USE_ALSA

#include "jdlib/miscmsg.h"

#include <string>
#include <asoundlib.h>

using namespace SOUND;


Play_Sound::Play_Sound()
    : m_playing( false )
{
#ifdef _DEBUG
    std::cout << "Play_Sound::Play_Sound\n";
#endif
}


Play_Sound::~Play_Sound()
{
#ifdef _DEBUG
    std::cout << "Play_Sound::~Play_Sound\n";
#endif

    // デストラクタの中からdispatchを呼ぶと落ちるので dispatch不可にする
    set_dispatchable( false );

    stop();
    wait();
}


void Play_Sound::stop()
{
    if( ! is_playing() ) return;

#ifdef _DEBUG
    std::cout << "Play_Sound::stop\n";
#endif

    m_stop = true;
    wait();
}


void Play_Sound::wait()
{
    m_thread.join();
}


//
// wav　再生スレッド起動
//
void Play_Sound::play( const std::string& wavfile )
{
    if( wavfile.empty() ) return;
    if( m_thread.is_running() ){
        MISC::ERRMSG( "Play_Sound::play : thread has been running" );
        return;
    }

    m_wavfile = wavfile;
    m_stop = false;

    if( ! m_thread.create( ( STARTFUNC ) launcher, ( void * ) this, JDLIB::NODETACH ) ){
        MISC::ERRMSG( "Play_Sound::play : could not start thread" );
    }
    else{
        m_playing = true;
    }
}


//
// スレッドのランチャ (static)
//
void* Play_Sound::launcher( void* dat )
{
    Play_Sound* ps = ( Play_Sound * ) dat;
    ps->play_wavfile();
    return 0;
}


//
// wav 再生 スレッド
//
void Play_Sound::play_wavfile()
{
    if( m_wavfile.empty() ) return;

#ifdef _DEBUG
    std::cout << "Play_Sound::play_wavfile file = " << m_wavfile << std::endl;
#endif

    char *buffer = NULL;
    FILE* fin = NULL;
    snd_pcm_t *handle = NULL;

    try{

        fin = fopen( m_wavfile.c_str(), "rb" );
        if( ! fin ) throw "cannot open " + m_wavfile;

        // フォーマット取得
        size_t filepos = 0;

        RIFFCHK riffchk;
        size_t chksize = 8;
        filepos += fread( &riffchk, 1, chksize, fin );
        if( strncmp( riffchk.id, "RIFF", 4 ) != 0 ) throw m_wavfile + " is not a wave file";

        WAVEFMTCHK wavefmt;
        chksize = 28;
        filepos += fread( &wavefmt, 1, chksize, fin );
        if( strncmp( wavefmt.id, "WAVEfmt ", 8 ) != 0 ) throw m_wavfile + " is broken";
        if( wavefmt.fmt != 1 ) throw m_wavfile + " is not a PCM format";

        // データチャンクまでseek
        DATACHK datachk;
        chksize = 8;
        for(;;){
            fseek( fin, filepos, SEEK_SET );
            if( ! fread( &datachk, 1, chksize, fin ) ) throw m_wavfile + " is broken";
            if( strncmp( datachk.id, "data", 4 ) == 0 ) break;
            ++filepos;
        }

#ifdef _DEBUG
        std::cout << "rate = " << wavefmt.rate << std::endl
                  << "chn = " << wavefmt.chn << std::endl
                  << "bit = " << wavefmt.bit << std::endl
                  << "sec = " << (double)datachk.size/wavefmt.average << std::endl;
#endif

        // デバイスオープン
        const char *device = "default";
        int err = snd_pcm_open( &handle, device, SND_PCM_STREAM_PLAYBACK, 0 );
        if( err < 0 || ! handle ) throw std::string( "cannot open sound device : " ) + snd_strerror( err );

        // パラメータ設定
        const int msec = 100;
 	snd_pcm_format_t pcmfm = ( wavefmt.bit == 8 ? SND_PCM_FORMAT_U8 : SND_PCM_FORMAT_S16_LE );
        err = snd_pcm_set_params(
            handle,
            pcmfm,
            SND_PCM_ACCESS_RW_INTERLEAVED,
            wavefmt.chn,
            wavefmt.rate,
            1, // リサンプリングする
            msec * 1000 // period の秒数( msec * 1000 )
            );
        if( err < 0 ) throw std::string( "failed to set parameter : " ) + snd_strerror( err );

        // バッファのメモリ確保
        snd_pcm_uframes_t buffer_size;
        snd_pcm_uframes_t period_size; 
        snd_pcm_get_params( handle, &buffer_size, &period_size );
        size_t bufsize = period_size * wavefmt.block;
        buffer = new char[ bufsize + 64 ];

#ifdef _DEBUG
        std::cout << "period = " << period_size << ", bufsize = " << bufsize << std::endl;
        size_t totalsize = 0;
#endif
        while( ! m_stop ){

            memset( buffer, 0, bufsize );
            size_t readsize = fread( buffer, 1, bufsize , fin );
            if( ! readsize ) break;

#ifdef _DEBUG
            totalsize += readsize;
            std::cout << totalsize << " / " << datachk.size << std::endl;
#endif

            snd_pcm_sframes_t frames = snd_pcm_writei( handle, buffer, readsize / wavefmt.block );
            if( frames < 0 ) frames = snd_pcm_recover( handle, frames, 0 );  // レジューム
            if( frames < 0 || frames < ( snd_pcm_sframes_t ) ( readsize / wavefmt.block ) )
                throw std::string( "failed to snd_pcm_write : " ) + snd_strerror( err );
        }
    }
    catch( const std::string& err ){ MISC::ERRMSG( err ); }

    if( handle ) snd_pcm_close( handle );
    if( fin ) fclose( fin );
    if( buffer ) delete[] buffer;

#ifdef _DEBUG
    std::cout << "fin\n";
#endif

    dispatch();
}


//
// ディスパッチャのコールバック関数
//
void Play_Sound::callback_dispatch()
{
#ifdef _DEBUG
    std::cout << "Play_Sound::callback_dispatch\n";
#endif

    wait();
    m_playing = false;
}

#endif
