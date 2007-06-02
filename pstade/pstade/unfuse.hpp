#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_UNFUSE_HPP
#define PSTADE_UNFUSE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This could be implementedy by 'compose' with 'pack',
// but this is the basis together with 'fuse'.


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/deferred.hpp>
#include <pstade/pack.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/use_default.hpp>


namespace pstade {


    namespace unfuse_detail {


        template<class FusedFun, class NullaryResult, class PackFun>
        struct return_op :
            callable<return_op<FusedFun, NullaryResult, PackFun>, NullaryResult>
        {
            template<class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A)>
            struct apply
            { }; // complete for SFINAE.

            // 0ary
            template< class Result >
            Result call() const
            {
                return m_fun(
                    m_pack_fun()
                );
            }

            // 1ary-
            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/unfuse.hpp>))
            #include BOOST_PP_ITERATE()

            explicit return_op()
            { }

            explicit return_op(FusedFun f, PackFun p) :
                m_fun(f), m_pack_fun(p)
            { }

            typedef FusedFun base_type;

            FusedFun base() const
            {
                return m_fun;
            }

        private:
            FusedFun m_fun;
            PackFun m_pack_fun;
        };



        struct can_take_empty_tuple;

        template<class FusedFun, class Pack>
        struct apply_empty_tuple :
            boost::result_of<
                PSTADE_DEFERRED(FusedFun const)(
                    typename boost::result_of<PSTADE_DEFERRED(Pack const)()>::type
                )
            >
        { };

        template<class NullaryResult, class FusedFun, class PackFun>
        struct nullary_result_aux :
            boost::mpl::eval_if< boost::is_same<can_take_empty_tuple, NullaryResult>,
                apply_empty_tuple<FusedFun, PackFun>,
                boost::mpl::identity<NullaryResult>
            >
        { };


    } // namespace unfuse_detail


    typedef
        unfuse_detail::can_take_empty_tuple
    nullary_fused;


    // The nullary result type is passed explicitly
    // for a function which can't take an empty tuple.

    template<class NullaryResult = boost::use_default>
    struct op_unfuse :
        callable< op_unfuse<NullaryResult> >
    {
        template<class Myself, class FusedFun, class PackFun = op_pack const>
        struct apply
        {
            typedef typename
                pass_by_value<PackFun>::type
            pack_fun_t;

            typedef typename
                pass_by_value<FusedFun>::type
            fused_fun_t;

            typedef typename
                unfuse_detail::nullary_result_aux<NullaryResult, fused_fun_t, pack_fun_t>::type
            nullary_result_t;

            typedef
                unfuse_detail::return_op<fused_fun_t, nullary_result_t, pack_fun_t>
            type;
        };

        template<class Result, class FusedFun, class Pack>
        Result call(FusedFun& f, Pack& p) const
        {
            return Result(f, p);
        }

        template<class Result, class FusedFun>
        Result call(FusedFun& f) const
        {
            return (*this)(f, pack);
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
        PSTADE_DEFERRED(FusedFun const)(
            typename boost::result_of<
                PSTADE_DEFERRED(PackFun const)(PSTADE_PP_ENUM_PARAMS_WITH(n, A, &))
            >::type
        )
    >
{ };

template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
{
    return m_fun(
        m_pack_fun(BOOST_PP_ENUM_PARAMS(n, a))
    );
}


#undef n
#endif
