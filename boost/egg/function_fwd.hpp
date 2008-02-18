#ifndef BOOST_EGG_FUNCTION_FWD_HPP
#define BOOST_EGG_FUNCTION_FWD_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/boost_use_default_fwd.hpp>
#include <boost/egg/register_nullary_result.hpp>


namespace boost { namespace egg {


    typedef use_default by_perfect;
    struct by_ref;
    struct by_cref;
    struct by_value;


    template<class Little, class Strategy = by_perfect>
    struct function;

    #define BOOST_EGG_FUNCTION_L {
    #define BOOST_EGG_FUNCTION_R }
    #define BOOST_EGG_FUNCTION(L) BOOST_EGG_FUNCTION_L L BOOST_EGG_FUNCTION_R


} } // namespace boost::egg


BOOST_EGG_REGISTER_NULLARY_RESULT_OF_TEMPLATE(boost::egg::function, (class)(class))


#include <boost/egg/detail/suffix.hpp>
#endif
