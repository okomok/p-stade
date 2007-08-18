#ifndef PSTADE_EGG_DETAIL_ADD_CONST_REFERENCE_HPP
#define PSTADE_EGG_DETAIL_ADD_CONST_REFERENCE_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>


namespace pstade { namespace egg { namespace detail {


    template<class A>
    struct add_const_reference :
        boost::add_reference<
            typename boost::add_const<A>::type
        >
    { };


} } } // namespace pstade::egg::detail


#endif
