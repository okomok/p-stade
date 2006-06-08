#ifndef PSTADE_HAMBURGER_DESKTOP_HPP
#define PSTADE_HAMBURGER_DESKTOP_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/instance.hpp>
#include <pstade/lime/find.hpp>
#include <pstade/oven/equal.hpp>
#include <pstade/require.hpp>
#include <pstade/statement.hpp>
#include "./element.hpp"
#include "./factory.hpp"


namespace pstade { namespace hamburger {


PSTADE_INSTANCE(const ustring, desktop_name, ("desktop"))


// Question:
// workarea is better name?
//
// no writable to keep thread-safety
//
struct desktop :
    element
{
protected:
    rectangle impl_bounds() const
    {
        rectangle rc;
        PSTADE_REQUIRE(::SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0));
        return rc;
    }
};


namespace desktop_detail {


    PSTADE_STATEMENT(Register,
        hamburger::register_element<desktop>("desktop");
    )


    inline
    bool is_desktop(element& elem)
    {
        return oven::equals(elem.name(), desktop_name);
    }


} // namespace desktop_detail


inline
rectangle desktop_bounds(element& elem)
{
    boost::optional<element&> top = lime::find_up(elem, desktop_detail::is_desktop);
    BOOST_ASSERT(top);

    return (*top).bounds();
}


} } // namespace pstade::hamburger


#endif
