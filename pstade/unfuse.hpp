#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_UNFUSE_HPP
#define PSTADE_UNFUSE_HPP
#include "./prelude.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This could be implementedy by 'compose' with 'tuple_pack',
// but this is the basis together with 'fuse'.


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/deferred.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/tuple.hpp> // tuple_pack
#include <pstade/use_default.hpp>
#include <pstade/use_nullary_result.hpp>


namespace pstade {


    namespace unfuse_detail {


        template<class Function, class NullaryResult, class Pack>
        struct return_op :
            callable<return_op<Function, NullaryResult, Pack>, NullaryResult>
        {
            template<class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A)>
            struct apply
            { }; // complete for SFINAE.

            // 0ary
            template< class Result >
            Result call() const
            {
                return m_fun(
                    m_pack()
                );
            }

            // 1ary-
            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/unfuse.hpp>))
            #include BOOST_PP_ITERATE()

            explicit return_op()
            { }

            explicit return_op(Function f, Pack p) :
                m_fun(f), m_pack(p)
            { }

            typedef Function base_type;

            Function base() const
            {
                return m_fun;
            }

        private:
            Function m_fun;
            Pack m_pack;
        };



        template<class Function, class Pack>
        struct apply_empty_tuple :
            boost::result_of<
                PSTADE_DEFERRED(Function const)(
                    typename boost::result_of<PSTADE_DEFERRED(Pack const)()>::type
                )
            >
        { };


        template<class NullaryResult, class Function, class Pack>
        struct nullary_result_aux :
            use_nullary_result_eval_to<
                NullaryResult,
                apply_empty_tuple<Function, Pack>
            >
        { };


    } // namespace unfuse_detail


    // If 'NullaryResult' is 'boost::use_default', this is not nullary-callable.
    // Else if 'NullaryResult' is 'use_nullary_result', 'Function' is considered
    // as callable with an empty tuple, then the result is inspected.
    // Otherwise, a passed type is the result type of this.

    template<class NullaryResult = boost::use_default>
    struct op_unfuse :
        callable< op_unfuse<NullaryResult> >
    {
        template<class Myself, class Function, class Pack = op_tuple_pack const>
        struct apply
        {
            typedef typename
                pass_by_value<Pack>::type
            pack_t;

            typedef typename
                pass_by_value<Function>::type
            fun_t;

            typedef typename
                unfuse_detail::nullary_result_aux<NullaryResult, fun_t, pack_t>::type
            nullary_result_t;

            typedef
                unfuse_detail::return_op<fun_t, nullary_result_t, pack_t>
            type;
        };

        template<class Result, class Function, class Pack>
        Result call(Function& f, Pack& p) const
        {
            return Result(f, p);
        }

        template<class Result, class Function>
        Result call(Function& f) const
        {
            return (*this)(f, tuple_pack);
        }
    };


    PSTADE_CONSTANT(unfuse, (op_unfuse<>))


} // namespace pstade


PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE(pstade::unfuse_detail::return_op, 3)


#endif
#else
#define n BOOST_PP_ITERATION()


template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
    boost::result_of<
        PSTADE_DEFERRED(Function const)(
            typename boost::result_of<
                PSTADE_DEFERRED(Pack const)(PSTADE_PP_ENUM_PARAMS_WITH(n, A, &))
            >::type
        )
    >
{ };

template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
{
    return m_fun(
        m_pack(BOOST_PP_ENUM_PARAMS(n, a))
    );
}


#undef n
#endif
