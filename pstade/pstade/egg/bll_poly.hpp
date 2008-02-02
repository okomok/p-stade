#ifndef PSTADE_EGG_BLL_POLY_HPP
#define PSTADE_EGG_BLL_POLY_HPP
#include "./detail/prefix.hpp"


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
#include <pstade/pod_constant.hpp>
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./construct_braced2.hpp"
#include "./detail/little_bll_poly_result.hpp"
#include "./generator.hpp"


namespace pstade { namespace egg {


    template<class Bindable, class Strategy = by_perfect>
    struct result_of_bll_poly
    {
        typedef
            function<detail::little_bll_poly_result<Bindable, boost::mpl::false_>, Strategy>
        type;
    };

    #define PSTADE_EGG_BLL_POLY_L { {
    #define PSTADE_EGG_BLL_POLY_R } }
    #define PSTADE_EGG_BLL_POLY(F) PSTADE_EGG_BLL_POLY_L F PSTADE_EGG_BLL_POLY_R


    typedef
        generator<
            result_of_bll_poly< deduce<mpl_1, as_value> >::type,
            by_value,
            X_construct_braced2<>
        >::type
    T_bll_poly;

    PSTADE_POD_CONSTANT((T_bll_poly), bll_poly) = PSTADE_EGG_GENERATOR();


    template<class Bindable>
    struct result_of_bll_poly_nullary
    {
        typedef
            function<detail::little_bll_poly_result<Bindable, boost::mpl::true_>, by_ref>
        type;
    };


    typedef
        generator<
            result_of_bll_poly_nullary< deduce<mpl_1, as_value> >::type,
            by_value,
            X_construct_braced2<>
        >::type
    T_bll_poly_nullary;

    PSTADE_POD_CONSTANT((T_bll_poly_nullary), bll_poly_nullary) = PSTADE_EGG_GENERATOR();


} } // namespace pstade::egg


#endif
