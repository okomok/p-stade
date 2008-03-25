#ifndef BOOST_EGG_DETAIL_RESULT_OF_TUPLE_GET_HPP
#define BOOST_EGG_DETAIL_RESULT_OF_TUPLE_GET_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/affect.hpp>
#include <boost/egg/detail/tuple_element.hpp>


namespace boost { namespace egg { namespace details {


    template<int N, class Tuple>
    struct result_of_tuple_get :
        affect<
            Tuple &,
            typename tuple_element<N, Tuple>::type
        >
    { };


} } } // namespace boost::egg::details


#endif
