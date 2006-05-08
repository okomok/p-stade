#ifndef PSTADE_HAMBURGER_ELEMENT_HPP
#define PSTADE_HAMBURGER_ELEMENT_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <boost/assert.hpp>
#include <boost/microsoft/atl/win.hpp> // CMessageMap
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/optional.hpp>
#include <pstade/instance.hpp>
#include <pstade/lime/node.hpp>
#include <pstade/oven/joint_range.hpp>
#include <pstade/oven/sequence_cast.hpp>
#include <pstade/tomato/boolean_cast.hpp>
#include <pstade/unused.hpp>
#include <pstade/ustring.hpp>
#include "./element_attributes.hpp"
#include "./rectangle.hpp"


namespace pstade { namespace hamburger {


struct element_interface :
    ATL::CMessageMap
{
    void create()
    {
        impl_detail_pre_create();
        return impl_create();
    }

    HWND window() const
    {
        return impl_window();
    }

    bool is_windowless() const
    {
        return impl_is_windowless();
    }

    void set_bounds(rectangle bounds)
    {
        m_bounds = bounds;
    }

    rectangle get_bounds() const
    {
        return m_bounds;
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
    {
        BOOST_ASSERT(false);
        pstade::unused(hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);
        return FALSE;
    }

protected:
    virtual void impl_create() // = 0;
    {
        BOOST_ASSERT(false);
    }

    virtual HWND impl_window() const
    {
        return NULL;
    }

    virtual bool impl_is_windowless() const
    {
        return true;
    }

// private:
    virtual void impl_detail_pre_create() // = 0;
    {
        BOOST_ASSERT(false);
    }

private:
    rectangle m_bounds;
};


typedef lime::node<element_interface>
element_node;


struct element :
    element_node
{
    explicit element()
    {
        hamburger::set_default_element_attributes(*this);
    }

protected:
    void impl_detail_pre_create()
    {
        hamburger::set_default_element_dependent_attributes(*this);
    }
};


} } // namespace pstade::hamburger


#endif
