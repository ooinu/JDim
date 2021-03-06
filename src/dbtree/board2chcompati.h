// ライセンス: GPL2

//
// 2ch 互換型板
//

#ifndef _BOARD2CHCOMPATI_H
#define _BOARD2CHCOMPATI_H

#include "boardbase.h"

namespace DBTREE
{
    class SettingLoader;
    class RuleLoader;

    class Board2chCompati : public BoardBase
    {
        SettingLoader* m_settingloader;
        RuleLoader* m_ruleloader;

      public:

        Board2chCompati( const std::string& root, const std::string& path_board, const std::string& name, const std::string& basicauth );
        ~Board2chCompati();

        // 書き込み用クッキー
        std::string cookie_for_write() override;

        // 書き込み時に必要なキーワード( hana=mogera や suka=pontan など )を
        // 確認画面のhtmlから解析する      
        void analyze_keyword_for_write( const std::string& html ) override;

        // 新スレ作成用のメッセージ変換
        std::string create_newarticle_message( const std::string& subject, const std::string& name,
                                               const std::string& mail, const std::string& msg ) override;

        // 新スレ作成用のbbscgi のURL
        std::string url_bbscgi_new() override;
        
        // 新スレ作成用のsubbbscgi のURL
        std::string url_subbbscgi_new() override;

        // ローカルルール
        std::string localrule() override;

        // SETTING.TXT 
        std::string settingtxt() override;
        std::string default_noname() override;
        int line_number() override;
        int message_count() override;
        std::string get_unicode() override;

      private:

        bool is_valid( const std::string& filename ) override;

        ArticleBase* append_article( const std::string& datbase, const std::string& id, const bool cached ) override;
        void parse_subject( const char* str_subject_txt ) override;
        void regist_article( const bool is_online ) override;

        void load_rule_setting() override;
        void download_rule_setting() override;

        // レス数であぼーん(グローバル)
        int get_abone_number_global() override;
    };
}

#endif
