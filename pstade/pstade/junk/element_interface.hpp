#ifndef PSTADE_HAMBURGER_ELEMENT_INTERFACE_HPP
#define PSTADE_HAMBURGER_ELEMENT_INTERFACE_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/atl/win.hpp> // CMessageMap
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/tomato/boolean_cast.hpp>
#include <pstade/unused.hpp>
#include "./dimension.hpp"
#include "./graphics.hpp"
#include "./point.hpp"


namespace pstade { namespace hamburger {


struct element_interface :
    ATL::CMessageMap
{
    void create()
    {
        impl_detail_pre_create();
        return impl_create();
    }

    HWND get_window() const
    {
        return impl_get_window();
    }

    bool is_windowless() const
    {
        return impl_is_windowless();
    }

    void set_location(point lc)
    {
        return impl_set_location(lc);
    }

    point get_location() const
    {
        return impl_get_location();
    }

    void set_size(dimension sz)
    {
        return impl_set_size(sz);
    }

    dimension get_size() const
    {
        return impl_get_size();
    }

    void paint(graphics gr)
    {
        return impl_paint(gr);
    }

    void show()
    {
        return impl_show();
    }

    bool process_message(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID = 0)
    {
        return tomato::boolean(ProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID));
    }

    // Workaround:
    // BOOST_FOREACH doesn't allow abstract types.(will be fixed.)
    //
public:
    virtual BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
    { pstade::unused(hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID); throw 0; }

protected:
    virtual void impl_create()              { throw 0; }
    virtual HWND impl_get_window() const    { throw 0; }
    virtual bool impl_is_windowless() const { throw 0; }
    virtual void impl_set_location(point)   { throw 0; }
    virtual point impl_get_location() const { throw 0; }
    virtual void impl_set_size(dimension)   { throw 0; }
    virtual dimension impl_get_size() const { throw 0; }
    virtual void impl_paint(graphics)       { throw 0; }
    virtual void impl_show()                { throw 0; }

// private:
    virtual void impl_detail_pre_create()   { throw 0; }
};


} } // namespace pstade::hamburger


#endif
