#ifndef BOOST_EGG_UNCURRY_HPP
#define BOOST_EGG_UNCURRY_HPP
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
#include <boost/egg/construct_braced2.hpp>
#include <boost/egg/detail/derived_from.hpp>
#include <boost/egg/detail/little_uncurry_result.hpp>
#include <boost/egg/generator.hpp>


namespace boost { namespace egg {


    template<class Base, class Strategy = by_perfect>
    struct result_of_uncurry
    {
        typedef
            function<details::little_uncurry_result<Base, Strategy>, Strategy>
        type;
    };

    #define BOOST_EGG_UNCURRY_L { {
    #define BOOST_EGG_UNCURRY_R } }
    #define BOOST_EGG_UNCURRY(F) BOOST_EGG_UNCURRY_L F BOOST_EGG_UNCURRY_R


    template<class Strategy = by_perfect>
    struct X_uncurry : details::derived_from_eval<
        generator<
            typename result_of_uncurry<deduce<mpl::_1, as_value>, Strategy>::type,
            by_value,
            X_construct_braced2<>
        > >
    { };

    typedef X_uncurry<>::base_class T_uncurry;
    BOOST_EGG_CONST((T_uncurry), uncurry) = BOOST_EGG_GENERATOR();


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
