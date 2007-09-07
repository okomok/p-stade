#ifndef PSTADE_EGG_DETAIL_META_ARG_HPP
#define PSTADE_EGG_DETAIL_META_ARG_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_reference.hpp>


namespace pstade { namespace egg { namespace detail {


    // Add const-qualifier if rvalue is specified.
    //     int        -> int const
    //     int&       -> int
    //     int const& -> int const
    template<class A>
    struct meta_arg :
        boost::remove_reference<
            // msvc warns against 'A const' if 'A' is reference.
            typename boost::add_const<A>::type
        >
    { };


    // Always const-qualified
    template<class A>
    struct meta_carg :
        boost::add_const<
            typename boost::remove_reference<A>::type
        >
    { };


} } } // namespace pstade::egg::detail


#endif
