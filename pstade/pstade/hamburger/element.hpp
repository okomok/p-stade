#ifndef PSTADE_HAMBURGER_ELEMENT_HPP
#define PSTADE_HAMBURGER_ELEMENT_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/sdk/windows.hpp>
#include <pstade/instance.hpp>
#include <pstade/lime/node.hpp>
#include <pstade/lime/ustring.hpp>
#include <pstade/oven/joint_range.hpp>
#include "./rect.hpp"


namespace pstade { namespace hamburger {


struct element_interface
{
    virtual void set_visible(bool v)
    { set_visible_impl(v); }

protected:
    virtual void set_visible_impl(bool v) = 0;
};


typedef lime::node<element_interface>
element_node;


PSTADE_INSTANCE(const lime::ustring, n_href,                ("href"))
PSTADE_INSTANCE(const lime::ustring, n_accName,             ("accName"))
PSTADE_INSTANCE(const lime::ustring, n_accDescription,      ("accDescription"))
PSTADE_INSTANCE(const lime::ustring, n_accKeyboardShortcut, ("accKeyboardShortcut"))
PSTADE_INSTANCE(const lime::ustring, n_alphaBlend,          ("alphaBlend"))
PSTADE_INSTANCE(const lime::ustring, n_clippingColor,       ("clippingColo"))
PSTADE_INSTANCE(const lime::ustring, n_clippingImage,       ("clippingImage"))
PSTADE_INSTANCE(const lime::ustring, n_elementType,         ("elementTyp"))
PSTADE_INSTANCE(const lime::ustring, n_enabled,             ("enabled"))
PSTADE_INSTANCE(const lime::ustring, n_height,              ("height"))
PSTADE_INSTANCE(const lime::ustring, n_horizontalAlignment, ("horizontalAlignment"))
PSTADE_INSTANCE(const lime::ustring, n_id,                  ("id"))
PSTADE_INSTANCE(const lime::ustring, n_left,                ("left"))
PSTADE_INSTANCE(const lime::ustring, n_passThrough,         ("passThrough"))
PSTADE_INSTANCE(const lime::ustring, n_tabStop,             ("tabStop"))
PSTADE_INSTANCE(const lime::ustring, n_top,                 ("top"))
PSTADE_INSTANCE(const lime::ustring, n_verticalAlignment,   ("verticalAlignment"))
PSTADE_INSTANCE(const lime::ustring, n_visible,             ("visible"))
PSTADE_INSTANCE(const lime::ustring, n_width,               ("width"))
PSTADE_INSTANCE(const lime::ustring, n_zIndex,              ("zIndex"))


PSTADE_INSTANCE(const lime::ustring, v_true,    ("true"))
PSTADE_INSTANCE(const lime::ustring, v_false,   ("false"))
PSTADE_INSTANCE(const lime::ustring, v_auto,    ("auto"))
PSTADE_INSTANCE(const lime::ustring, v_left,    ("left"))
PSTADE_INSTANCE(const lime::ustring, v_top,     ("top"))
PSTADE_INSTANCE(const lime::ustring, v_right,   ("right"))
PSTADE_INSTANCE(const lime::ustring, v_bottom,  ("bottom"))
PSTADE_INSTANCE(const lime::ustring, v_center,  ("center"))
PSTADE_INSTANCE(const lime::ustring, v_stretch, ("stretch"))
PSTADE_INSTANCE(const lime::ustring, v_zero,    ("0"))


struct element :
    element_node
{
    explicit element(lime::ustring name) :
        element_node(name)
    { }

    explicit element(element_node& parent, lime::ustring name) :
        element_node(parent, name)
    {
        set_default_values();
    }

protected:
    // element_interface
    //
    virtual void set_visible_impl(bool )
    { }

private:
    void set_default_values()
    {
        att(n_alphaBlend)           = "255";
        att(n_clippingColor)        = v_auto;
        att(n_elementType)          = name();
        att(n_enabled)              = v_true;
        att(n_height)               = v_zero;
        att(n_horizontalAlignment)  = v_left;
        att(n_left)                 = v_zero;
        att(n_passThrough)          = v_false;
        att(n_tabStop)              = v_true;
        att(n_top)                  = v_zero;
        att(n_verticalAlignment)    = v_top;
        att(n_visible)              = v_true;
        att(n_width)                = v_zero;
        att(n_zIndex)               = v_zero;

        att(n_id)       = lime::ustring("unnamed_")|oven::jointed(name());
        att(n_accName)  = att(n_id);
    }
};


} } // namespace pstade::hamburger


#endif
