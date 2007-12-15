// ライセンス: GPL2

//#define _DEBUG
#include "jddebug.h"

#include "articlemachi.h"
#include "nodetreemachi.h"
#include "interface.h"

#include "jdlib/miscutil.h"
#include "jdlib/misctime.h"

#include <sstream>

using namespace DBTREE;


ArticleMachi::ArticleMachi( const std::string& datbase, const std::string& _id, bool cached )
    : ArticleBase( datbase, _id, cached )
{
    assert( !id().empty() );

    // Machi の場合は拡張子が無いので key = id
    set_key( get_id() );

    // key から since 計算
    set_since_time( atol( get_key().c_str() ) );
    set_since_date( MISC::timettostr( get_since_time() ) );
}


ArticleMachi::~ArticleMachi()
{}


const std::string ArticleMachi::create_write_message( const std::string& name, const std::string& mail, const std::string& msg )
{
    if( msg.empty() ) return std::string();

    std::string charset = DBTREE::board_charset( get_url() );

    std::stringstream ss_post;
    ss_post.clear();
    ss_post << "BBS="      << DBTREE::board_id( get_url() )
            << "&KEY="     << get_key()
            << "&TIME="    << get_time_modified()
            << "&submit="  << MISC::charset_url_encode( "書き込む", charset )
            << "&NAME="    << MISC::charset_url_encode( name, charset )
            << "&MAIL="    << MISC::charset_url_encode( mail, charset )
            << "&MESSAGE=" << MISC::charset_url_encode( msg, charset );

#ifdef _DEBUG
    std::cout << "ArticleMachi::create_write_message " << ss_post.str() << std::endl;
#endif

    return ss_post.str();
}




//
// bbscgi のURL
//
// (例) "http://www.machi.to/bbs/write.cgi"
//
//
const std::string ArticleMachi::url_bbscgi()
{
    std::string cgibase = DBTREE::url_bbscgibase( get_url() );
    return cgibase.substr( 0, cgibase.length() -1 ); // 最後の '/' を除く
}


//
// subbbscgi のURL
//
// (例) "http://www.machi.to/bbs/write.cgi"
//
const std::string ArticleMachi::url_subbbscgi()
{
    std::string cgibase = DBTREE::url_subbbscgibase( get_url() );
    return cgibase.substr( 0, cgibase.length() -1 ); // 最後の '/' を除く
}



NodeTreeBase* ArticleMachi::create_nodetree()
{
#ifdef _DEBUG
    std::cout << "ArticleMachi::create_nodetree " << url() << std::endl;
#endif

    return new NodeTreeMachi( get_url(), get_date_modified() );
}
