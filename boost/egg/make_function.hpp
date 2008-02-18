#ifndef BOOST_EGG_MAKE_FUNCTION_HPP
#define BOOST_EGG_MAKE_FUNCTION_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/by_perfect.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/construct_braced1.hpp>
#include <boost/egg/detail/derived_from.hpp>
#include <boost/egg/generator.hpp>


namespace boost { namespace egg {


    template<class Strategy = by_perfect>
    struct X_make_function : details::derived_from_eval<
        generator<
            function<deduce<mpl::_1, as_value>, Strategy>,
            by_value,
            X_construct_braced1<>
        > >
    { };

    typedef X_make_function<>::base_class T_make_function;
    BOOST_EGG_CONST((T_make_function), make_function) = BOOST_EGG_GENERATOR();


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
