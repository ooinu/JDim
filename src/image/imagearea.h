// ライセンス: GPL2

//
// メイン画像クラス
//

#ifndef _IMAGEAREA_H
#define _IMAGEAREA_H

#include "imageareabase.h"

namespace IMAGE
{
    class ImageAreaMain : public ImageAreaBase
    {
      public:

        ImageAreaMain( const std::string& url );
        virtual ~ImageAreaMain();

        virtual void show_image();
    };
}

#endif
