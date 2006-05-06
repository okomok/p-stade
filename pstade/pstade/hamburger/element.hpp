#ifndef PSTADE_HAMBURGER_ELEMENT_HPP
#define PSTADE_HAMBURGER_ELEMENT_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
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


namespace pstade { namespace hamburger {


// Workaround:
// BOOST_FOREACH (for now) doesn't allow abstract types.
//
struct element_interface :
    ATL::CMessageMap
{
    bool process(HWND hWnd, UINT uMsg,
        WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
    {
        return tomato::boolean(ProcessWindowMessage(hWnd, uMsg,
            wParam, lParam, lResult, dwMsgMapID));
    }

    void create()
    {
        create_impl();
    }

    boost::optional<HWND> hwnd() const
    {
        return hwnd_impl();
    }

public:
    virtual BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg,
        WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
    {
        pstade::unused(hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);
        return FALSE;
    }

protected:
    virtual void create_impl() const
    { }

    virtual boost::optional<HWND> hwnd_impl() const
    {
        return boost::optional<HWND>();
    }
};


typedef lime::node<element_interface>
element_node;


struct element :
    element_node
{
    explicit element()
    {
        set_default_values();
    }

private:
    void set_default_values()
    {
        att(Name_alphaBlend)            = "255";
        att(Name_clippingColor)         = Value_auto;
        //att(Name_elementType)         = name();
        att(Name_enabled)               = Value_true;
        att(Name_height)                = Value_zero;
        att(Name_horizontalAlignment)   = Value_left;
        att(Name_left)                  = Value_zero;
        att(Name_passThrough)           = Value_false;
        att(Name_tabStop)               = Value_true;
        att(Name_top)                   = Value_zero;
        att(Name_verticalAlignment)     = Value_top;
        att(Name_visible)               = Value_true;
        att(Name_width)                 = Value_zero;
        att(Name_zIndex)                = Value_zero;

        //att(Name_id)       = ustring("unnamed_")|oven::jointed(name());
        //att(Name_accName)  = att(Name_id);
    }
};


} } // namespace pstade::hamburger


#endif
