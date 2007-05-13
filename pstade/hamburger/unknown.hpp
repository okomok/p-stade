#ifndef PSTADE_HAMBURGER_UNKNOWN_HPP
#define PSTADE_HAMBURGER_UNKNOWN_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/ketchup.hpp>
#include "./element.hpp"


namespace pstade { namespace hamburger {


struct unknown :
    ketchup::message_processor<unknown, element>
{
    begin_msg_map
    <
        empty_entry<>
    >
    end_msg_map;
};


} } // namespace pstade::hamburger


#endif
