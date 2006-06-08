#ifndef PSTADE_HAMBURGER_VIEW_HPP
#define PSTADE_HAMBURGER_VIEW_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/foreach.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/thread/thread.hpp>
#include <pstade/apple/atl/win.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/apple/wtl/gdi.hpp> // CPaintDC
#include <pstade/apple/wtl/frame.hpp> // CMessageFilter, CIdleHandler
#include <pstade/instance.hpp>
#include <pstade/ketchup/core.hpp>
#include <pstade/oven/sort_range.hpp>
#include <pstade/tomato/diet/valid.hpp>
#include <pstade/tomato/idle_handling.hpp>
#include <pstade/tomato/message_filtering.hpp>
#include <pstade/tomato/message_loop.hpp>
#include <pstade/tomato/rgb.hpp>
#include <pstade/tomato/window/create_result.hpp>
#include <pstade/tomato/window/wnd_class.hpp>
#include <pstade/unused.hpp>
#include <pstade/require.hpp>
#include <pstade/ustring.hpp>
#include "./detail/caption.hpp"
#include "./detail/chain_mouse_message.hpp"
#include "./detail/background.hpp"
#include "./detail/handle_wm_erasebkgnd.hpp"
#include "./detail/initial_view_bounds.hpp"
#include "./detail/layout.hpp"
#include "./detail/optional_zero.hpp"
#include "./detail/quit_on_destroy.hpp"
#include "./detail/transparency.hpp"
#include "./dimension.hpp"
#include "./element.hpp"
#include "./graphics.hpp"
#include "./has_transparency_color.hpp"
#include "./is_visible.hpp"
#include "./location.hpp"
#include "./log.hpp"
#include "./size.hpp"
#include "./rectangle.hpp"
#include "./refresh.hpp"
#include "./view_attributes.hpp"
#include "./z_order.hpp"


namespace pstade { namespace hamburger {


namespace view_detail {


    template< class ViewT >
    struct impl
    {
        typedef ATL::CWindowImpl<
            ViewT,
            ATL::CWindow,
            ATL::CWinTraits<
                // same as wmp10
                WS_OVERLAPPED|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
                WS_EX_APPWINDOW
            >
        > type;
    };


    // 'boost::thread_group' seems unrecommanded.
    PSTADE_INSTANCE(boost::thread_group, threads, value)


} // namespace view_detail


struct view :
    ketchup::message_processor<view,
        view_detail::impl<view>::type,
        element
    >,
    WTL::CMessageFilter,
    WTL::CIdleHandler
{
private:
    typedef view_detail::impl<view>::type impl_t;

public:
    static ATL::CWndClassInfo& GetWndClassInfo() {
        return tomato::wnd_class<view>(_T("pstade::hamburger::view"));
    }

public:
    explicit view()
    {
        hamburger::set_default_view_attributes(*this);
    }

    BOOL OnIdle() // override
    {
        return FALSE;
    }

    BOOL PreTranslateMessage(MSG* pMsg) // override
    {
        pstade::unused(pMsg);
        return FALSE;
    }

protected:
    void impl_create()
    {
        BOOST_ASSERT(!diet::valid(m_hWnd));

        view_detail::threads.add_thread(new boost::thread(boost::lambda::bind(&view::work, this)));
    }

    boost::optional<HWND> impl_window() const
    {
        BOOST_ASSERT(diet::valid(m_hWnd));

        return boost::optional<HWND>(m_hWnd);
    }

    void impl_set_bounds(rectangle rc)
    {
        rc += hamburger::location(*parent());
        MoveWindow(rc.left, rc.top, rc.Width(), rc.Height(), TRUE);
    }

    rectangle impl_bounds() const
    {
        rectangle rc;
        GetWindowRect(rc);

        rc -= hamburger::location(*parent());
        return rc;
    }

friend class ketchup::access;
    LRESULT on_create(CREATESTRUCT *pst)
    {
        set_msg_handled(false);

        detail::reset_caption(*this);
        detail::reset_transparency(*this);

        // must be in this thread.
        BOOST_FOREACH (element& child, m_self) {
            child.create();
        }

        pstade::unused(pst);
        return tomato::create_success;
    }

    void on_close()
    {
        set_msg_handled(false);

        rectangle rc = bounds();
        *this%Name_left   = pstade::lexical(rc.left);
        *this%Name_top    = pstade::lexical(rc.top);
        *this%Name_width  = pstade::lexical(rc.Width());
        *this%Name_height = pstade::lexical(rc.Height());
    }

    void on_paint(HDC)
    {
        if (hamburger::has_transparency_color(*this))
            return on_paint_transparency();

        // See: OnPaint, atlhost.h, ATL7
        //
        WTL::CPaintDC dc(m_hWnd);
        if (dc.IsNull())
            return;

        rectangle rc;
        GetClientRect(rc);

        WTL::CBitmap bitmap(::CreateCompatibleBitmap(dc, rc.Width(), rc.Height()));
        if (bitmap.IsNull())
            return;

        WTL::CDC dcCompatible(::CreateCompatibleDC(dc));
        if (dcCompatible.IsNull())
            return;

        WTL::CBitmapHandle bitmapOld(dcCompatible.SelectBitmap(bitmap));
        if (bitmapOld.IsNull())
            return;

        detail::paint_background(*this, dcCompatible, rc);

        BOOST_FOREACH (element& child, m_self|oven::sorted(z_order)) {
            child.paint(dcCompatible, child.bounds());
        }

        dc.BitBlt(0, 0, rc.right, rc.bottom, dcCompatible, 0, 0, SRCCOPY);
        dcCompatible.SelectBitmap(bitmapOld);
    }

    void on_paint_transparency()
    {
        WTL::CPaintDC dc(m_hWnd);

        rectangle rc;
        dc.GetClipBox(&rc);
        detail::paint_background(*this, dc, rc);

        BOOST_FOREACH (element& child, m_self|oven::sorted(z_order)) {
            rectangle b = child.bounds();
            if (!(rc & b).IsRectEmpty())
                child.paint(dc, b);
        }
    }

    void on_size(UINT uType, dimension sz)
    {
        set_msg_handled(false);

        if (uType == SIZE_MINIMIZED) {
            // Workaround: flicker
            detail::remove_transparency(*this);
            return;
        }

        detail::layout(*this);
        pstade::unused(sz);
    }

    void on_getminmaxinfo(MINMAXINFO* pinfo)
    {
        detail::optional_zero(pinfo->ptMinTrackSize.x, *this, Name_minWidth);
        detail::optional_zero(pinfo->ptMinTrackSize.y, *this, Name_minHeight);
        detail::optional_zero(pinfo->ptMaxTrackSize.x, *this, Name_maxWidth);
        detail::optional_zero(pinfo->ptMaxTrackSize.y, *this, Name_maxHeight);
    }

    void on_syscommand(UINT uType, point pt)
    {
        set_msg_handled(false);

        if (uType == SC_RESTORE) {
            // Workaround: flicker
            // There seems no performance difference with or without this.
            detail::reset_transparency(*this);
        }

        pstade::unused(pt);
    }

    void on_lbuttondown(UINT uFlags, point pt)
    {
        ShowWindow(SW_SHOWMINIMIZED);
        pstade::unused(uFlags, pt);
    }

    void on_rbuttondown(UINT uFlags, point pt)
    {
        PostMessage(WM_CLOSE);
        pstade::unused(uFlags, pt);
    }

    begin_msg_map
    <
        msg_wm_create<&_::on_create>,
        msg_wm_paint<&_::on_paint>,
        msg_wm_size<&_::on_size>,
        msg_wm_getminmaxinfo<&_::on_getminmaxinfo>,
        detail::handle_wm_erasebkgnd<>,
        detail::chain_mouse_message<>,
        msg_wm_rbuttondown<&_::on_rbuttondown>,
        msg_wm_syscommand<&_::on_syscommand>,
        //msg_wm_close<&_::on_close>,
        detail::quit_on_destroy<>,
        empty_entry<>
    >
    end_msg_map;

private:
    void work()
    {
        try {
            tomato::message_loop loop;

            if (!hamburger::is_visible(*this))
                return;

            rectangle rc = detail::initial_view_bounds(*this);
            PSTADE_REQUIRE(Create(NULL, rc));

            tomato::message_filtering filtering(this);
            tomato::idle_handling idling(this);

            ShowWindow(SW_SHOWNORMAL);

            loop.run();
        }
        // catch here cause boost::thread will catch all.
        catch (std::exception& err) {
            log << err.what();
        }
    }
};


inline
void view_join_all()
{
    view_detail::threads.join_all();
}


namespace view_detail {


    PSTADE_STATEMENT(Register,
        hamburger::register_element<view>("view");
    )


} // namespace view_detail


} } // namespace pstade::hamburger


#endif
