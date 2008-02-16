// ライセンス: GPL2

//
// 画像ポップアップクラス
//

#ifndef _IMAGEVIEWPOPUP_H
#define _IMAGEVIEWPOPUP_H

#include "imageviewbase.h"

namespace IMAGE
{
    class ImageViewPopup : public ImageViewBase
    {
        Gtk::EventBox m_event_frame;
        Gtk::EventBox m_event_margin;
        Gtk::Label* m_label;
        size_t m_length_prev;

      public:

        ImageViewPopup( const std::string& url );
        virtual ~ImageViewPopup();

        virtual void clock_in();

        virtual void stop();
        virtual void show_view();

      private:

        void update_label();
        void set_label( const std::string& status );
        void remove_label();
    };

}

#endif

