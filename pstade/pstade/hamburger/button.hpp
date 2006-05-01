#ifndef PSTADE_HAMBURGER_BUTTON_HPP
#define PSTADE_HAMBURGER_BUTTON_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/ketchup.hpp>
#include <pstade/lime/ustring.hpp>
#include "./element.hpp"
#include "./factory.hpp"


namespace pstade { namespace hamburger {


struct button :
    ketchup::message_processor<button, element>
{
    begin_msg_map
    <
        empty_entry<>
    >
    end_msg_map;
};


namespace button_detail { namespace {
    

    entry_type entry = hamburger::register_node<button>("button");
    

} } // namespace button_detail::unnamed


} } // namespace pstade::hamburger


#endif
