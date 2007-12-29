#ifndef PSTADE_OVEN_DETAIL_RANGE_BASED_LL_HPP
#define PSTADE_OVEN_DETAIL_RANGE_BASED_LL_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <pstade/egg/by_cref.hpp>
#include <pstade/egg/defer_sig.hpp>
#include <pstade/pod_constant.hpp>
#include "./range_based1.hpp"
#include "./range_based2.hpp"


namespace pstade { namespace oven { namespace detail {


// Pass by_cref; large arity is needed.
template< class SigFun >
struct range_based1_sig_fun :
    result_of_range_based1<
        typename egg::result_of_defer_sig<SigFun, egg::by_cref>::type
    >
{ };

template< class SigFun >
struct range_based2_sig_fun :
    result_of_range_based2<
        typename egg::result_of_defer_sig<SigFun, egg::by_cref>::type
    >
{ };


#define PSTADE_OVEN_RANGE_BASED1_LL(R, _, Name) \
    typedef \
        pstade::oven::detail::range_based1_sig_fun< boost::lambda::ll::Name >::type \
    BOOST_PP_CAT(T_, Name); \
    \
    PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_, Name)), Name) \
        = PSTADE_OVEN_RANGE_BASED1_L PSTADE_OVEN_RANGE_BASED_LL_init PSTADE_OVEN_RANGE_BASED1_R; \
/**/

#define PSTADE_OVEN_RANGE_BASED2_LL(R, _, Name) \
    typedef \
        pstade::oven::detail::range_based2_sig_fun< boost::lambda::ll::Name >::type \
    BOOST_PP_CAT(T_, Name); \
    \
    PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_, Name)), Name) \
        = PSTADE_OVEN_RANGE_BASED2_L PSTADE_OVEN_RANGE_BASED_LL_init PSTADE_OVEN_RANGE_BASED2_R; \
/**/


    #define PSTADE_OVEN_RANGE_BASED_LL_init \
        PSTADE_EGG_DEFER_SIG({}) \
    /**/


} } } // namespace pstade::oven::detail


#endif
