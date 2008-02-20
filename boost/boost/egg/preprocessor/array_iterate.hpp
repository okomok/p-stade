#ifndef BOOST_EGG_PREPROCESSOR_ARRAY_ITERATE_HPP
#define BOOST_EGG_PREPROCESSOR_ARRAY_ITERATE_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/array/size.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/tuple/elem.hpp>


#define BOOST_EGG_PP_ARRAY_ITERATE() \
    <boost/egg/preprocessor/detail/array_iterate_include.hpp> \
/**/

#define BOOST_EGG_PP_ARRAY_ITERATION() \
    BOOST_PP_ARRAY_ELEM(BOOST_PP_ITERATION(), BOOST_EGG_PP_ARRAY_ITERATION_array) \
/**/


#endif
