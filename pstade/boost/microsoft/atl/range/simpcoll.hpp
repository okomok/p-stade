#ifndef BOOST_MICROSOFT_ATL_RANGE_SIMPCOLL_HPP
#define BOOST_MICROSOFT_ATL_RANGE_SIMPCOLL_HPP


// Boost.Microsoft
//
// Copyright 2006 Shunsuke Sogame.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/atl/config.hpp> // ATL_HAS_OLD_SIMPLE_ARRAY
#include <boost/microsoft/atl/range/detail/coll_value_type.hpp>
#include <boost/microsoft/atl/range/detail/simple_array_tag.hpp>
#include <boost/microsoft/atl/simpcoll_fwd.hpp>
#include <boost/microsoft/detail/range/customize.hpp>


#if !defined(BOOST_MICROSOFT_ATL_HAS_OLD_CSIMPLEARRAY)

    BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE(
        boost::microsoft::atl::range_detail::simple_array_tag,
        (ATL, BOOST_PP_NIL), CSimpleArray, 2
    )

#else

    BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE(
        boost::microsoft::atl::range_detail::simple_array_tag,
        (ATL, BOOST_PP_NIL), CSimpleArray, 1
    )

    BOOST_MICROSOFT_RANGE_CUSTOMIZE_TEMPLATE(
        boost::microsoft::atl::range_detail::simple_array_tag,
        (ATL, BOOST_PP_NIL), CSimpleValArray, 1
    )

#endif


#endif
