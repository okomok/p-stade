#ifndef PSTADE_HAMBURGER_ELEMENT_HPP
#define PSTADE_HAMBURGER_ELEMENT_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/foreach.hpp>
#include <boost/optional.hpp>
#include <pstade/apple/atl/win.hpp> // CMessageMap
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/lime/node_facade.hpp>
#include <pstade/tomato/boolean_cast.hpp>
#include <pstade/unused.hpp>
#include "./element_attributes.hpp"
#include "./graphics.hpp"
#include "./is_visible.hpp"
#include "./rectangle.hpp"


namespace pstade { namespace hamburger {


namespace element_detail {


    template< class Element >
    void pre_create(Element& elem)
    {
        hamburger::set_default_element_dependent_attributes(elem);
    }


} // namespace element_detail


struct element :
    lime::node_facade<element>,
    ATL::CMessageMap
{
    element() :
        m_self(*this), m_created(false)
    {
        hamburger::set_default_element_attributes(*this);   
    }

    // interfaces
    //
    void create()
    {
        BOOST_ASSERT(!m_created);

        m_created = true;
        element_detail::pre_create(*this);
        override_create();
    }

    void destroy()
    {
        BOOST_ASSERT(m_created);
        m_created = false;
        override_destroy();
    }

    boost::optional<HWND> window() const
    {
        boost::optional<HWND> wnd = override_window();
        BOOST_ASSERT(wnd ? ::IsWindow(*wnd) : true);

        return wnd;
    }

    void set_bounds(rectangle rc)
    {
        return override_set_bounds(rc);
    }

    rectangle bounds() const
    {
        return override_bounds();
    }

    void paint(graphics g, rectangle rc)
    {
        boost::optional<element&> pa = parent();
        if (pa && !hamburger::is_visible(*pa))
            return;

        if (!hamburger::is_visible(*this))
            return;

        override_paint(g, rc);
    }

    bool process_message(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID = 0)
    {
        return ProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)|tomato::booleanized;
    }

    // overridables
    //
public:
    BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID) // override
    {
        pstade::unused(hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);
        return FALSE;
    }

protected:
    virtual void override_create()
    {
        BOOST_FOREACH (element& child, m_self) {
            child.create();
        }
    }

    virtual void override_destroy()
    {
        BOOST_FOREACH (element& child, m_self) {
            child.destroy();
        }
    }

    virtual boost::optional<HWND> override_window() const
    {
        return boost::optional<HWND>();
    }

    virtual void override_set_bounds(rectangle rc)
    {
        pstade::unused(rc);
    }

    virtual rectangle override_bounds() const
    {
        return rectangle(0, 0, 0, 0);
    }

    virtual void override_paint(graphics g, rectangle rc)
    {
        pstade::unused(g, rc);
    }

    // VC++ workaround for BOOST_FOREACH(..., *this)
    element& m_self;

private:
    bool m_created;
};


} } // namespace pstade::hamburger


#endif
