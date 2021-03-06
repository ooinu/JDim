// ライセンス: GPL2

//#define _DEBUG
#include "jddebug.h"

#include "sidebaritempref.h"

#include "icons/iconmanager.h"
#include "jdlib/miscutil.h"

#include "global.h"
#include "session.h"
#include "command.h"

using namespace CORE;


SidebarItemPref::SidebarItemPref( Gtk::Window* parent, const std::string& url )
    : SKELETON::SelectItemPref( parent, url )
{
    // デフォルトの項目を設定
    append_default_pair( ITEM_NAME_SEARCHBOX, ICON::get_icon( ICON::TRANSPARENT ) );
    append_default_pair( ITEM_NAME_SEARCH_NEXT, ICON::get_icon( ICON::SEARCH_NEXT ) );
    append_default_pair( ITEM_NAME_SEARCH_PREV, ICON::get_icon( ICON::SEARCH_PREV ) );
    append_default_pair( ITEM_NAME_CHECK_UPDATE_ROOT, ICON::get_icon( ICON::CHECK_UPDATE_ROOT ) );
    append_default_pair( ITEM_NAME_CHECK_UPDATE_OPEN_ROOT, ICON::get_icon( ICON::CHECK_UPDATE_OPEN_ROOT ) );
    append_default_pair( ITEM_NAME_STOPLOADING, ICON::get_icon( ICON::STOPLOADING ) );
    append_default_pair( ITEM_NAME_SEPARATOR, ICON::get_icon( ICON::TRANSPARENT ) );

    // 文字列を元に列を追加
    append_rows( SESSION::get_items_sidebar_toolbar_str() );

    set_title( "ツールバー項目設定(サイドバー)" );
}


// OKを押した
void SidebarItemPref::slot_ok_clicked()
{
    SESSION::set_items_sidebar_toolbar_str( get_items() );
    CORE::core_set_command( "update_bbslist_toolbar_button" );
}


//
// デフォルトボタン
//
void SidebarItemPref::slot_default()
{
    append_rows( SESSION::get_items_sidebar_toolbar_default_str() );
}
