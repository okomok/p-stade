#ifndef PSTADE_OVEN_DETAIL_RANGE_BASED_LL_HPP
#define PSTADE_OVEN_DETAIL_RANGE_BASED_LL_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/constant.hpp>
#include "../range_based1.hpp"
#include "../range_based2.hpp"
#include "./sig_forward.hpp"


namespace pstade { namespace oven { namespace detail {


template< class SigFun >
struct range_based1_sig_fun :
    boost::result_of<
        op_range_based1(sig_forward_result<SigFun>)
    >
{ };

template< class SigFun >
struct range_based2_sig_fun :
    boost::result_of<
        op_range_based2(sig_forward_result<SigFun>)
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
