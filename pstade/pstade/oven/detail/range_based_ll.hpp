#ifndef PSTADE_OVEN_DETAIL_RANGE_BASED_LL_HPP
#define PSTADE_OVEN_DETAIL_RANGE_BASED_LL_HPP
#include "../prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/constant.hpp>
#include "./deferred_sig.hpp"
#include "./range_based1.hpp"
#include "./range_based2.hpp"


namespace pstade { namespace oven { namespace detail {


template< class SigFun >
struct range_based1_sig_fun :
    boost::result_of<
        op_range_based1(
            typename boost::result_of<op_deferred_sig(SigFun)>::type
        )
    >
{ };

template< class SigFun >
struct range_based2_sig_fun :
    boost::result_of<
        op_range_based2(
            typename boost::result_of<op_deferred_sig(SigFun)>::type
        )
    >
{ };


#define PSTADE_OVEN_DETAIL_RANGE_BASED1_LL(R, _, Name) \
    typedef \
        ::pstade::oven::detail::range_based1_sig_fun< ::boost::lambda::ll::Name >::type \
    BOOST_PP_CAT(op_, Name); \
    \
    PSTADE_CONSTANT(Name, (BOOST_PP_CAT(op_, Name))) \
/**/

#define PSTADE_OVEN_DETAIL_RANGE_BASED2_LL(R, _, Name) \
    typedef \
        ::pstade::oven::detail::range_based2_sig_fun< ::boost::lambda::ll::Name >::type \
    BOOST_PP_CAT(op_, Name); \
    \
    PSTADE_CONSTANT(Name, (BOOST_PP_CAT(op_, Name))) \
/**/


} } } // namespace pstade::oven::detail


#endif
