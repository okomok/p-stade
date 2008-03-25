#ifndef BOOST_EGG_DETAIL_FUNCTION_PREAMBLE_HPP
#define BOOST_EGG_DETAIL_FUNCTION_PREAMBLE_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/bll/sig_impl.hpp>
#include <boost/egg/detail/little_of.hpp>
#include <boost/egg/detail/nullary_result_of_little.hpp>
#include <boost/egg/detail/of_apply_little.hpp>
#include <boost/egg/detail/strategy_of.hpp>

   
#define BOOST_EGG_FUNCTION_PREAMBLE() \
    \
    typedef typename \
        details::little_of<function>::type \
    little_type; \
    \
    typedef typename \
        details::strategy_of<function>::type \
    strategy_type; \
    \
    typedef typename \
        details::nullary_result_of_little<little_type, function>::type \
    nullary_result_type; \
    \
    template<class FunCall> \
    struct result : \
        details::of_apply_little<FunCall> \
    { }; \
    \
    template<class FunArgs> \
    struct sig : \
        bll_sig_impl<FunArgs> \
    { }; \
    \
    little_type const &base() const \
    { \
        return this->little(); \
    } \
    \
/**/


#endif
