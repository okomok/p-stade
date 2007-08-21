#ifndef PSTADE_OVEN_REGULAR_HPP
#define PSTADE_OVEN_REGULAR_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Oven can't call this automatically for lambda functors,
// for it is impossible to implement neither "is_assignable"
// nor "is_default_constructible". Also, notice that
// 'is_lambda_functor' can't be the detection;
// e.g. 'perfect(lambda::_1)', which is neither assignable
// nor a lambda functor.
//
// These could be...
//   egg::indirected(make_regularized(f))      // regular
//   egg::indirected(make_shared_ptr(new F())) // regular_c, shared_regular
//   egg::indirected(&f)                       // regular_ref
// , which would be cumbersome.


#include <boost/shared_ptr.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/egg/deferred.hpp>
#include <pstade/egg/indirected.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include <pstade/result_of_lambda.hpp> // inclusion guaranteed
#include "./detail/regularized.hpp"


namespace pstade { namespace oven {


namespace regular_detail {


    template< class Function >
    struct base
    {
        typedef typename
            pass_by_value<Function>::type
        fun_t;

        typedef
            detail::regularized<fun_t>
        reg_t;

        typedef typename
            result_of<egg::op_indirected(reg_t)>::type
        result_type;

        result_type operator()(Function& fun) const
        {
            return egg::indirected(reg_t(fun));
        }
    };


    template< class Function >
    struct base_c
    {
        typedef typename
            pass_by_value<Function>::type
        fun_t;

        typedef
            boost::shared_ptr<fun_t>
        pf_t;

        typedef typename
            result_of<egg::op_indirected(pf_t)>::type
        result_type;

        result_type operator()(Function& fun) const
        {
            return egg::indirected(pf_t(new fun_t(fun)));
        }
    };


    template< class Function >
    struct base_ref
    {
        typedef typename
            result_of<egg::op_indirected(Function *)>::type
        result_type;

        result_type operator()(Function& fun) const
        {
            return egg::indirected(boost::addressof(fun));
        }
    };


} // namespace regular_detail


typedef PSTADE_EGG_DEFER((regular_detail::base<boost::mpl::_>)) op_regular;
PSTADE_POD_CONSTANT((op_regular), regular) = PSTADE_EGG_DEFERRED;

typedef PSTADE_EGG_DEFER((regular_detail::base_c<boost::mpl::_>)) op_regular_c;
PSTADE_POD_CONSTANT((op_regular_c), regular_c) = PSTADE_EGG_DEFERRED;

typedef PSTADE_EGG_DEFER((regular_detail::base_ref<boost::mpl::_>)) op_regular_ref;
PSTADE_POD_CONSTANT((op_regular_ref), regular_ref) = PSTADE_EGG_DEFERRED;


} } // namespace pstade::oven


#endif
