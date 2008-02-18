#ifndef BOOST_EGG_BLL_EXTENSION_FWD_HPP
#define BOOST_EGG_BLL_EXTENSION_FWD_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace boost { namespace lambda {

    template<class Act, class A1>
    struct return_type_1;

    template<class Act, class A1, class A2>
    struct return_type_2;

    template<class Act, class Args>
    struct return_type_N;

    template<class Act, class A1>
    struct plain_return_type_1;

    template<class Act, class A1, class A2>
    struct plain_return_type_2;

    template<class Func>
    struct function_adaptor;

    class member_pointer_action;

} }

#include <boost/config.hpp> // BOOST_STATIC_CONSTANT
#include <boost/type_traits/remove_cv.hpp>


#include <boost/lambda/detail/actions.hpp>
#include <boost/lambda/detail/operator_actions.hpp>


#include <boost/egg/detail/suffix.hpp>
#endif
