#ifndef PSTADE_OVEN_REGULAR_HPP
#define PSTADE_OVEN_REGULAR_HPP
#include "./prelude.hpp"


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
//   make_indirect_function(make_regularized(f))       // regular
//   make_indirect_function(make_shared_ptr(new F()))  // regular_c, shared_regular
//   make_indirect_function(boost::addressof(f))       // regular_ref
// , which would be cumbersome.


#include <boost/shared_ptr.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/result_of_lambda.hpp> // inclusion guaranteed
#include "./detail/indirect_function.hpp"
#include "./detail/regularized.hpp"


namespace pstade { namespace oven {


namespace regular_detail {


    template< class Function >
    struct baby
    {
        typedef typename
            pass_by_value<Function>::type
        fun_t;

        typedef
            detail::regularized<fun_t>
        reg_t;

        typedef
            detail::indirect_function<reg_t>
        result_type;

        result_type operator()(Function& fun) const
        {
            return result_type(reg_t(fun));
        }
    };


    template< class Function >
    struct baby_c
    {
        typedef typename
            pass_by_value<Function>::type
        fun_t;

        typedef
            boost::shared_ptr<fun_t>
        pf_t;

        typedef
            detail::indirect_function<pf_t>
        result_type;

        result_type operator()(Function& fun) const
        {
            return result_type(pf_t(new fun_t(fun)));
        }
    };


    template< class Function >
    struct baby_ref
    {
        typedef
            detail::indirect_function<Function *>
        result_type;

        result_type operator()(Function& fun) const
        {
            return result_type(boost::addressof(fun));
        }
    };


} // namespace regular_detail


PSTADE_FUNCTION(regular, (regular_detail::baby<_>))
PSTADE_FUNCTION(regular_c, (regular_detail::baby_c<_>))
PSTADE_FUNCTION(regular_ref, (regular_detail::baby_ref<_>))


} } // namespace pstade::oven


#endif
