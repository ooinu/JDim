// ライセンス: 最新のGPL

#include "prefdiagfactory.h"

#include "passwdpref.h"
#include "browserpref.h"
#include "proxypref.h"

#include "board/preference.h"
#include "article/preference.h"
#include "image/preference.h"

SKELETON::PrefDiag* CORE::PrefDiagFactory( int type, const std::string& url )
{
    switch( type )
    {
        case PREFDIAG_PASSWD:
            return new CORE::PasswdPref( url );

        case PREFDIAG_BROWSER:
            return new CORE::BrowserPref( url );

        case PREFDIAG_PROXY:
            return new CORE::ProxyPref( url );

        case PREFDIAG_BOARD:
            return new BOARD::Preferences( url );

        case PREFDIAG_ARTICLE:
            return new ARTICLE::Preferences( url );

        case PREFDIAG_IMAGE:
            return new IMAGE::Preferences( url );

        default:
            return NULL;
    }
}

