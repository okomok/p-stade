#ifndef PSTADE_HAMBURGER_DESKTOP_HPP
#define PSTADE_HAMBURGER_DESKTOP_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/instance.hpp>
#include <pstade/lime/ustring.hpp>
#include "./element.hpp"
#include "./factory.hpp"


namespace pstade { namespace hamburger {


PSTADE_INSTANCE(const lime::ustring, desktop_name, ("desktop"))


struct desktop :
    element
{
    // structors
    //
    explicit desktop(element_node& parent) :
        element(parent, desktop_name)
    {
    }

protected:
    // element_interface
    //
    virtual void set_visible_impl(bool )
    { }
};


namespace desktop_detail { namespace {
    

    entry_type entry = hamburger::register_node<desktop>(desktop_name);
    

} } // namespace desktop_detail::unnamed


} } // namespace pstade::hamburger


#endif
