#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_PIPABLE_HPP
#define PSTADE_EGG_PIPABLE_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// 'boost::result_of' doesn't work with an array reference
// under weird VC++7.1.


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <boost/type_traits/add_const.hpp>
#include <pstade/instance.hpp>
#include <pstade/nonassignable.hpp>
#include <pstade/unparenthesize.hpp>
#include "./baby_call.hpp"
#include "./baby_result.hpp"
#include "./detail/config.hpp" // PSTADE_EGG_PIPABLE_MAX_ARITY
#include "./detail/pipes.hpp"
#include "./is_pipe.hpp" // as_pipe


namespace pstade { namespace egg {


template< class BabyFunction >
struct pipe :
    private as_pipe< pipe<BabyFunction> >,
    private nonassignable
{

    // structors
    //
    BabyFunction m_baby;

    explicit pipe()
    { }

    explicit pipe(BabyFunction const& baby) :
        m_baby(baby)
    { }


    // 0ary
    //
    detail::pipe0<BabyFunction
    > const
    operator()(
    ) const
    {
        return detail::pipe0<BabyFunction
        >(m_baby);
    }


    // 1ary
    //
    template< class A0 >
    detail::pipe1<BabyFunction,
        A0
    > const
    operator()(
        A0& a0
    ) const
    {
        return detail::pipe1<BabyFunction,
            A0
        >(m_baby, a0);
    }

    template< class A0 >
    detail::pipe1<BabyFunction,
        typename boost::add_const<A0>::type
    > const
    operator()(
        A0 const& a0
    ) const
    {
        return detail::pipe1<BabyFunction,
            typename boost::add_const<A0>::type
        >(m_baby, a0);
    }


    // 2ary -
    //
    #define PSTADE_EGG_call_operator(R, BitSeq) \
        template< BOOST_PP_ENUM_PARAMS(n, class A) > \
        detail::BOOST_PP_CAT(pipe, n)<BabyFunction, \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_EGG_arg_type, ~, BitSeq) \
        > const \
        operator()( \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_EGG_param, ~, BitSeq) \
        ) const \
        { \
            return detail::BOOST_PP_CAT(pipe, n)<BabyFunction, \
                BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_EGG_arg_type, ~, BitSeq) \
            >( m_baby, BOOST_PP_ENUM_PARAMS(n, a) ); \
        } \
    /**/


    #define PSTADE_EGG_arg_type(R, _, Index, Bit) \
        BOOST_PP_COMMA_IF(Index) BOOST_PP_CAT(PSTADE_EGG_ac, Bit)(BOOST_PP_CAT(A, Index)) \
    /**/


    #define PSTADE_EGG_param(R, _, Index, Bit) \
        BOOST_PP_COMMA_IF(Index) \
        BOOST_PP_CAT(A, Index) BOOST_PP_CAT(PSTADE_EGG_c, Bit) & BOOST_PP_CAT(a, Index) \
    /**/

                   
    #define PSTADE_EGG_c0
    #define PSTADE_EGG_c1 const


    // Workaround:
    // VC++7.1 is somewhat broken with array reference.
    #define PSTADE_EGG_ac0(X) X
    #define PSTADE_EGG_ac1(X) typename boost::add_const< X >::type


    #define PSTADE_EGG_bits(Z, N, _) ((0)(1))


    #define BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_EGG_PIPABLE_MAX_ARITY, <pstade/egg/pipable.hpp>))
    #include BOOST_PP_ITERATE()


    #undef PSTADE_EGG_bits
    #undef PSTADE_EGG_ac1
    #undef PSTADE_EGG_ac0
    #undef PSTADE_EGG_c1
    #undef PSTADE_EGG_c0
    #undef PSTADE_EGG_param
    #undef PSTADE_EGG_arg_type
    #undef PSTADE_EGG_call_operator


}; // struct pipe


// passed as is
//
template< class Input, class BabyFunction > inline
typename baby_result1<BabyFunction,
    Input
>::type
operator|(Input& in, pipe<BabyFunction> const& pi)
{
    pstade::unused(pi);
    return egg::baby_call(pi.m_baby, in);
}

template< class Input, class BabyFunction > inline
typename baby_result1<BabyFunction,
    typename boost::add_const<Input>::type
>::type
operator|(Input const& in, pipe<BabyFunction> const& pi)
{
    pstade::unused(pi);
    return egg::baby_call(pi.m_baby, in);
}


} } // namespace pstade::egg


#define PSTADE_EGG_PIPABLE(Name, Baby) \
    PSTADE_INSTANCE( \
        pstade::egg::pipe< PSTADE_UNPARENTHESIZE(Baby) > const, \
        Name, value \
    ) \
/**/


#endif
#else
#define n BOOST_PP_ITERATION()


BOOST_PP_SEQ_FOR_EACH_PRODUCT(
    PSTADE_EGG_call_operator,
    BOOST_PP_REPEAT(n, PSTADE_EGG_bits, ~)
)


#undef n
#endif
