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
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/range_reference.hpp>


namespace pstade_oven_extension {


template< class AtlString, class Range >
AtlString pstade_oven_(copy_range<AtlString>, Range& rng,
    typename boost::enable_if< pstade::apple::is_ATL_string<AtlString> >::type * = 0)
{
    AtlString str;

    typedef typename pstade::oven::range_reference<Range>::type ref_t;
    BOOST_FOREACH (ref_t v, rng) {
        str.AppendChar(v);
    }

    return str;
}


template< class Range >
WTL::CString pstade_oven_(copy_range<WTL::CString>, Range& rng)
{
    WTL::CString str;

    typedef typename pstade::oven::range_reference<Range>::type ref_t;
    BOOST_FOREACH (ref_t v, rng) {
        str += v;
    }

    return str;
}


} // namespace pstade_oven_extension


#endif
