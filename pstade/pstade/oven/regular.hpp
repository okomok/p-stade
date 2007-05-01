#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OVEN_REGULAR_HPP
#define PSTADE_OVEN_REGULAR_HPP


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


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constable.hpp>
#include <pstade/function.hpp>
#include <pstade/indirect.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of_lambda.hpp> // inclusion guaranteed
#include "./detail/regularized.hpp"


namespace pstade { namespace oven {


namespace regular_detail {


    template< class Indirectable >
    struct function_of :
        boost::remove_reference<
            typename boost::result_of<op_indirect(Indirectable const&)>::type
        >
    { };


    template< class Indirectable >
    struct return_op :
        callable<
            return_op<Indirectable>,
            typename boost::result_of<PSTADE_CONSTABLE_TPL(typename function_of<Indirectable>::type)()>::type
        >
    {
        typedef typename function_of<Indirectable>::type base_type;

        template< class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A) >
        struct apply
        { }; // complete for SFINAE.

        // 0ary
        template< class Result >
        Result call() const
        {
            return (*m_ind)();
        }

        // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/oven/regular.hpp>))
        #include BOOST_PP_ITERATE()

        explicit return_op()
        { }

        explicit return_op(Indirectable const& ind) :
            m_ind(ind)
        { }

        typename boost::result_of<op_indirect(Indirectable const&)>::type
        base() const
        {
            return *m_ind;
        }

    private:
        Indirectable m_ind;
    };


    template< class Function >
    struct baby
    {
        typedef typename
            pass_by_value<Function>::type
        fun_t;

        typedef
            detail::regularized<fun_t>
        ind_t;

        typedef
            return_op<ind_t>
        result_type;

        result_type operator()(Function& fun) const
        {
            return result_type(ind_t(fun));
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
        ind_t;

        typedef
            return_op<ind_t>
        result_type;

        result_type operator()(Function& fun) const
        {
            return result_type(ind_t(new fun_t(fun)));
        }
    };


    template< class Function >
    struct baby_ref
    {
        typedef
            return_op<Function *>
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


PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE(pstade::oven::regular_detail::return_op, 1)


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Myself, BOOST_PP_ENUM_PARAMS(n, class A) >
struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
    boost::result_of<PSTADE_CONSTABLE_TPL(base_type)(PSTADE_PP_ENUM_PARAMS_WITH(n, A, &))>
{ };

template< class Result, BOOST_PP_ENUM_PARAMS(n, class A) >
Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
{
    return (*m_ind)(BOOST_PP_ENUM_PARAMS(n, a));
}


#undef n
#endif
