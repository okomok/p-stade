#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_PIPES_IPP
#define PSTADE_EGG_DETAIL_PIPES_IPP


// PStade.Egg
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Prefer reference to pointer for function types.


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/type_traits/add_const.hpp>
#include <pstade/nonassignable.hpp>
#include <pstade/unused.hpp>
#include "../baby_call.hpp"
#include "../baby_result.hpp"
#include "./config.hpp" // PSTADE_EGG_PIPABLE_MAX_ARITY
#include "./pipe_base.hpp"


namespace pstade { namespace egg { namespace detail {


    // 0ary
    //
    template< class BabyFunction >
    struct pipe0 :
        pipe_base,
        private nonassignable
    {
        BabyFunction m_baby;

        explicit pipe0(BabyFunction const& baby) :
            m_baby(baby)
        { } 
    };

    template< class Input, class BabyFunction > inline
    typename baby_result1<BabyFunction,
        Input
    >::type
    operator|(Input& in, pipe0<BabyFunction> const& pi)
    {
        pstade::unused(pi);
        return egg::baby_call(pi.m_baby, in);
    }

    template< class Input, class BabyFunction > inline
    typename baby_result1<BabyFunction,
        typename boost::add_const<Input>::type
    >::type
    operator|(Input const& in, pipe0<BabyFunction> const& pi)
    {
        pstade::unused(pi);
        return egg::baby_call(pi.m_baby, in);
    }


    // 1ary
    //
    template< class BabyFunction, class A0 >
    struct pipe1 :
        pipe_base,
        private nonassignable
    {
        BabyFunction m_baby;

        explicit pipe1(BabyFunction const& baby, A0& a0) :
            m_baby(baby),
            m_a0(a0)
        { }

        A0& m_a0;
    };

    template< class Input, class BabyFunction, class A0 > inline
    typename baby_result2<BabyFunction,
        Input,
        A0
    >::type
    operator|(Input& in, pipe1<BabyFunction, A0> const& pi)
    {
        return egg::baby_call(pi.m_baby, in, pi.m_a0);
    }

    template< class Input, class BabyFunction, class A0 > inline
    typename baby_result2<BabyFunction,
        typename boost::add_const<Input>::type,
        A0
    >::type
    operator|(Input const& in, pipe1<BabyFunction, A0> const& pi)
    {
        return egg::baby_call(pi.m_baby, in, pi.m_a0);
    }


    // 2ary
    //
    template< class BabyFunction, class A0, class A1 >
    struct pipe2 :
        pipe_base,
        private nonassignable
    {
        BabyFunction m_baby;

        explicit pipe2(BabyFunction const& baby, A0& a0, A1& a1) :
            m_baby(baby),
            m_a0(a0), m_a1(a1)
        { }

        A0& m_a0; A1& m_a1;
    };

    template< class Input, class BabyFunction, class A0, class A1 > inline
    typename baby_result3<BabyFunction,
        Input,
        A0, A1
    >::type
    operator|(Input& in, pipe2<BabyFunction, A0, A1> const& pi)
    {
        return egg::baby_call(pi.m_baby, in, pi.m_a0, pi.m_a1);
    }

    template< class Input, class BabyFunction, class A0, class A1 > inline
    typename baby_result3<BabyFunction,
        typename boost::add_const<Input>::type,
        A0, A1
    >::type
    operator|(const Input& in, pipe2<BabyFunction, A0, A1> const& pi)
    {
        return egg::baby_call(pi.m_baby, in, pi.m_a0, pi.m_a1);
    }


    // 3ary -
    //
    #define PSTADE_EGG_ctor_arg(Z, N, _)   BOOST_PP_CAT(A, N)& BOOST_PP_CAT(a, N)
    #define PSTADE_EGG_ctor_init(Z, N, _)  BOOST_PP_CAT(m_a, N)(BOOST_PP_CAT(a, N))
    #define PSTADE_EGG_member(Z, N, _)     BOOST_PP_CAT(A, N)& BOOST_PP_CAT(m_a, N);
    #define PSTADE_EGG_call_arg(Z, N, _)   pi.BOOST_PP_CAT(m_a, N)

    #define BOOST_PP_ITERATION_PARAMS_1 (3, (3, PSTADE_EGG_PIPABLE_MAX_ARITY, <pstade/egg/detail/pipes.hpp>))
    #include BOOST_PP_ITERATE()

    #undef PSTADE_EGG_call_arg
    #undef PSTADE_EGG_member
    #undef PSTADE_EGG_ctor_init
    #undef PSTADE_EGG_ctor_arg


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


template< class BabyFunction, BOOST_PP_ENUM_PARAMS(n, class A) >
struct BOOST_PP_CAT(pipe, n) :
    pipe_base,
    private nonassignable
{
    BabyFunction m_baby;

    explicit BOOST_PP_CAT(pipe, n)( BabyFunction const& baby, BOOST_PP_ENUM(n, PSTADE_EGG_ctor_arg, ~) ) :
        m_baby(baby),
        BOOST_PP_ENUM(n, PSTADE_EGG_ctor_init, ~)
    { }

    BOOST_PP_REPEAT(n, PSTADE_EGG_member, ~)
};

template< class Input, class BabyFunction, BOOST_PP_ENUM_PARAMS(n, class A) > inline
typename BOOST_PP_CAT(baby_result, BOOST_PP_INC(n))<BabyFunction,
    Input,
    BOOST_PP_ENUM_PARAMS(n, A)
>::type
operator|(Input& in, BOOST_PP_CAT(pipe, n)< BabyFunction, BOOST_PP_ENUM_PARAMS(n, A) > const& pi)
{
    return egg::baby_call( pi.m_baby,  in, BOOST_PP_ENUM(n, PSTADE_EGG_call_arg, ~) );
}

template< class Input, class BabyFunction, BOOST_PP_ENUM_PARAMS(n, class A) > inline
typename BOOST_PP_CAT(baby_result, BOOST_PP_INC(n))<BabyFunction,
    typename boost::add_const<Input>::type,
    BOOST_PP_ENUM_PARAMS(n, A)
>::type
operator|(Input const& in, BOOST_PP_CAT(pipe, n)< BabyFunction, BOOST_PP_ENUM_PARAMS(n, A) > const& pi)
{
    return egg::baby_call( pi.m_baby, in, BOOST_PP_ENUM(n, PSTADE_EGG_call_arg, ~) );
}


#undef n
#endif
