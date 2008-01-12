#ifndef BOOST_EGG_BLL_DEFER_HPP
#define BOOST_EGG_BLL_DEFER_HPP
#include "./detail/prefix.hpp"


// Boost.Egg
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
// a nullary-callable function must be identified by 'bll_defer_nullary'.


#include <boost/mpl/bool.hpp>
#include <boost/egg/pstade/pod_constant.hpp>
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./detail/little_bll_defer_result.hpp"
#include "./generator.hpp"
#include "./use_brace2.hpp"


namespace pstade { namespace egg {


    template<class SigFun, class Strategy = by_perfect>
    struct result_of_bll_defer
    {
        typedef
            function<detail::little_bll_defer_result<SigFun, boost::mpl::false_>, Strategy>
        type;
    };

    #define BOOST_EGG_BLL_DEFER_L { {
    #define BOOST_EGG_BLL_DEFER_R } }
    #define BOOST_EGG_BLL_DEFER(F) BOOST_EGG_BLL_DEFER_L F BOOST_EGG_BLL_DEFER_R

    typedef
        generator<
            result_of_bll_defer< deduce<boost::mpl::_1, as_value> >::type,
            boost::use_default,
            use_brace2,
            by_value
        >::type
    T_bll_defer;

    PSTADE_POD_CONSTANT((T_bll_defer), bll_defer) = BOOST_EGG_GENERATOR();


    template<class SigFun>
    struct result_of_bll_defer_nullary
    {
        typedef
            function<detail::little_bll_defer_result<SigFun, boost::mpl::true_>, by_ref>
        type;
    };

    typedef
        generator<
            result_of_bll_defer_nullary< deduce<boost::mpl::_1, as_value> >::type,
            boost::use_default,
            use_brace2,
            by_value
        >::type
    T_bll_defer_nullary;

    PSTADE_POD_CONSTANT((T_bll_defer_nullary), bll_defer_nullary) = BOOST_EGG_GENERATOR();


} } // namespace pstade::egg


#endif
