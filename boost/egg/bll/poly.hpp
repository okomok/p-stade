#ifndef BOOST_EGG_BLL_POLY_HPP
#define BOOST_EGG_BLL_POLY_HPP
#include <boost/egg/detail/prefix.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Converts a poor functor type holding 'sig'
// into the function which supports 'boost::result_of'.
//
// As we can't detect the arity without 'lambda::bind',
// a nullary-callable function must be identified by 'bll_poly_nullary'.


#include <boost/mpl/bool.hpp>
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/construct_braced2.hpp>
#include <boost/egg/detail/little_bll_poly_result.hpp>
#include <boost/egg/generator.hpp>


namespace boost { namespace egg {


    template<class Bindable, class Strategy = by_perfect>
    struct result_of_bll_poly
    {
        typedef
            function<details::little_bll_poly_result<Bindable, mpl::false_>, Strategy>
        type;
    };

    #define BOOST_EGG_BLL_POLY_L { {
    #define BOOST_EGG_BLL_POLY_R } }
    #define BOOST_EGG_BLL_POLY(F) BOOST_EGG_BLL_POLY_L F BOOST_EGG_BLL_POLY_R


    typedef
        generator<
            result_of_bll_poly< deduce<mpl::_1, as_value> >::type,
            by_value,
            X_construct_braced2<>
        >::type
    T_bll_poly;

    BOOST_EGG_CONST((T_bll_poly), bll_poly) = BOOST_EGG_GENERATOR();


    template<class Bindable>
    struct result_of_bll_poly_nullary
    {
        typedef
            function<details::little_bll_poly_result<Bindable, mpl::true_>, by_ref>
        type;
    };


    typedef
        generator<
            result_of_bll_poly_nullary< deduce<mpl::_1, as_value> >::type,
            by_value,
            X_construct_braced2<>
        >::type
    T_bll_poly_nullary;

    BOOST_EGG_CONST((T_bll_poly_nullary), bll_poly_nullary) = BOOST_EGG_GENERATOR();


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
