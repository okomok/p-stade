#ifndef PSTADE_HAMBURGER_SUBVIEW_HPP
#define PSTADE_HAMBURGER_SUBVIEW_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/instance.hpp>
#include "./element.hpp"
#include "./view.hpp"


namespace pstade { namespace hamburger {


struct subview :
    element
{
protected:
    // element
    //
    virtual void set_visible_impl(bool )
    { }

private:
    void set_default_values()
    {
        att(n_backgroundColor)              = v_none;
        att(n_backgroundImageHueShift)      = "0.0";
        att(n_backgroundImageSaturation)    = "1.0";
        att(n_backgroundTiled)              = v_false;
        att(n_resizeBackgroundImage)        = v_false;
    }
};


namespace subview_detail { namespace {
    

    entry_type entry = hamburger::register_node<subview>("subview");
    

} } // namespace subview_detail::unnamed


} } // namespace pstade::hamburger


#endif
