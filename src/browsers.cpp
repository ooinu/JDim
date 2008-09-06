// ライセンス: GPL2

#include "browsers.h"

enum
{
    MAX_TEXT = 256,
    BROWSER_NUM = 5
};

namespace CORE
{
    char browsers[ BROWSER_NUM ][ 2 ][ MAX_TEXT ]={

        { "ユーザ設定", "" },
        { "標準ブラウザ(xdg-open)",    "xdg-open \"%LINK\"" },
        { "firefox 1.5/2.0/3.0 以降", "firefox \"%LINK\"" },
        { "firefox 1.0*", "firefox -remote \"openURL(%LINK,new-tab)\"" },
        { "opera 9.*",    "opera -remote \"openURL(%LINK,new-tab)\"" }
    };

    std::string get_browser_label( int num ){

        if( num >= BROWSER_NUM ) return std::string();
        return browsers[ num ][ 0 ];
    }

    std::string get_browser_name( int num ){

        if( num >= BROWSER_NUM ) return std::string();
        return browsers[ num ][ 1 ];
    }
}
