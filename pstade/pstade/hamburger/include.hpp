#ifndef PSTADE_HAMBURGER_INCLUDE_HPP
#define PSTADE_HAMBURGER_INCLUDE_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/foreach.hpp>
#include <pstade/ketchup.hpp>
#include <pstade/lime/load_file.hpp>
#include <pstade/oven/sequence_cast.hpp>
#include <pstade/statement.hpp>
#include <pstade/ustring.hpp>
#include "./element.hpp"
#include "./factory.hpp"
#include "./lime.hpp"


namespace pstade { namespace hamburger {


PSTADE_INSTANCE(const ustring, Name_href, ("href"))


struct include :
    ketchup::message_processor<include, element>
{
    begin_msg_map
    <
        empty_entry<>
    >
    end_msg_map;

protected:
    void create_impl()
    {
        std::string path = oven::sequence_cast<std::string>(att(Name_href));
        // build_path(path, ...)
        lime::load_file(*this, path);

        include& self(*this);
        BOOST_FOREACH (element_node& child, self) {
            child.create();
        }
    }
};


namespace include_detail {


    PSTADE_STATEMENT(Register,
        hamburger::register_element<include>("include");
    )


} // namespace include_detail


} } // namespace pstade::hamburger


#endif
