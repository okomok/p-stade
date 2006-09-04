#ifndef PSTADE_TOMATO_OVEN_HPP
#define PSTADE_TOMATO_OVEN_HPP


// PStade.Tomato
//
// Olepyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/foreach.hpp>
#include <boost/utility/enable_if.hpp>
#include <pstade/apple/atl/is_ATL_string.hpp>
#include <pstade/apple/wtl/misc.hpp> // CString
#include <pstade/oven/range_reference.hpp>
#include <pstade/overload.hpp>


template< class T, class Range >
typename boost::enable_if<pstade::apple::is_ATL_string<T>,
T>::type pstade_oven_copy_range(Range& rng, pstade::overload<T>)
{
    T str;

    typedef typename pstade::oven::range_reference<Range>::type ref_t;
    BOOST_FOREACH (ref_t v, rng) {
        str.AppendChar(v);
    }

    return str;
}


template< class Range >
WTL::CString pstade_oven_copy_range(Range& rng, pstade::overload<WTL::CString>)
{
    WTL::CString str;

    typedef typename pstade::oven::range_reference<Range>::type ref_t;
    BOOST_FOREACH (ref_t v, rng) {
        str += v;
    }

    return str;
}


#endif
