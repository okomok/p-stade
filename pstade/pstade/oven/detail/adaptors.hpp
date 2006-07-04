#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OVEN_DETAIL_ADAPTORS_IPP
#define PSTADE_OVEN_DETAIL_ADAPTORS_IPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/utility/addressof.hpp> // for Boost.Lambda functors
#include <boost/type_traits/add_const.hpp>
#include <pstade/egg/baby_call.hpp>
#include <pstade/egg/baby_result_type.hpp>
#include <pstade/unused.hpp>
#include "./config.hpp" // RANGE_ADAPTOR_MAX_ARITY


namespace pstade { namespace oven { namespace detail_adaptors {


    // 0ary
    //
    template< class BabyAdaptor >
    struct adaptor0
    { };

    template< class Range, class BabyAdaptor > inline
    typename egg::baby_result1<BabyAdaptor,
        Range
    >::type
    operator|(Range& rng, adaptor0<BabyAdaptor> ad)
    {
        pstade::unused(ad);
        return egg::baby_call<BabyAdaptor>(rng);
    }

    template< class Range, class BabyAdaptor > inline
    typename egg::baby_result1<BabyAdaptor,
        typename boost::add_const<Range>::type
    >::type
    operator|(const Range& rng, adaptor0<BabyAdaptor> ad)
    {
        pstade::unused(ad);
        return egg::baby_call<BabyAdaptor>(rng);
    }


    // 1ary
    //
    template< class BabyAdaptor, class A0 >
    struct adaptor1
    {
        explicit adaptor1(A0& a0) :
            m_pa0(boost::addressof(a0))
        { }

        A0 *m_pa0;
    };

    template< class Range, class BabyAdaptor, class A0 > inline
    typename egg::baby_result2<BabyAdaptor,
        Range,
        A0
    >::type
    operator|(Range& rng, adaptor1<BabyAdaptor, A0> ad)
    {
        return egg::baby_call<BabyAdaptor>(rng, *ad.m_pa0);
    }

    template< class Range, class BabyAdaptor, class A0 > inline
    typename egg::baby_result2<BabyAdaptor,
        typename boost::add_const<Range>::type,
        A0
    >::type
    operator|(const Range& rng, adaptor1<BabyAdaptor, A0> ad)
    {
        return egg::baby_call<BabyAdaptor>(rng, *ad.m_pa0);
    }


    // 2ary
    //
    template< class BabyAdaptor, class A0, class A1 >
    struct adaptor2
    {
        explicit adaptor2(A0& a0, A1& a1) :
            m_pa0(boost::addressof(a0)), m_pa1(boost::addressof(a1))
        { }

        A0 *m_pa0; A1 *m_pa1;
    };

    template< class Range, class BabyAdaptor, class A0, class A1 > inline
    typename egg::baby_result3<BabyAdaptor,
        Range,
        A0, A1
    >::type
    operator|(Range& rng, adaptor2<BabyAdaptor, A0, A1> ad)
    {
        return egg::baby_call<BabyAdaptor>(rng, *ad.m_pa0, *ad.m_pa1);
    }

    template< class Range, class BabyAdaptor, class A0, class A1 > inline
    typename egg::baby_result3<BabyAdaptor,
        typename boost::add_const<Range>::type,
        A0, A1
    >::type
    operator|(const Range& rng, adaptor2<BabyAdaptor, A0, A1> ad)
    {
        return egg::baby_call<BabyAdaptor>(rng, *ad.m_pa0, *ad.m_pa1);
    }


    // 3ary -
    //
    #define PSTADE_OVEN_ctor_arg(Z, N, _)   BOOST_PP_CAT(A, N)& BOOST_PP_CAT(a, N)
    #define PSTADE_OVEN_ctor_init(Z, N, _)  BOOST_PP_CAT(m_pa, N)(boost::addressof(BOOST_PP_CAT(a, N)))
    #define PSTADE_OVEN_member(Z, N, _)     BOOST_PP_CAT(A, N) *BOOST_PP_CAT(m_pa, N);
    #define PSTADE_OVEN_call_arg(Z, N, _)   *ad.BOOST_PP_CAT(m_pa, N)

    #define BOOST_PP_ITERATION_PARAMS_1 (3, (3, PSTADE_OVEN_RANGE_ADAPTOR_MAX_ARITY, <pstade/oven/detail/adaptors.hpp>))
    #include BOOST_PP_ITERATE()

    #undef PSTADE_OVEN_call_arg
    #undef PSTADE_OVEN_member
    #undef PSTADE_OVEN_ctor_init
    #undef PSTADE_OVEN_ctor_arg


} } } // namespace pstade::oven::detail_adaptors


#endif
#else
#define n BOOST_PP_ITERATION()


template< class BabyAdaptor, BOOST_PP_ENUM_PARAMS(n, class A) >
struct BOOST_PP_CAT(adaptor, n)
{
    explicit BOOST_PP_CAT(adaptor, n)( BOOST_PP_ENUM(n, PSTADE_OVEN_ctor_arg, ~) ) :
        BOOST_PP_ENUM(n, PSTADE_OVEN_ctor_init, ~)
    { }

    BOOST_PP_REPEAT(n, PSTADE_OVEN_member, ~)
};

template< class Range, class BabyAdaptor, BOOST_PP_ENUM_PARAMS(n, class A) > inline
typename egg::BOOST_PP_CAT(baby_result, BOOST_PP_INC(n))<BabyAdaptor,
    Range,
    BOOST_PP_ENUM_PARAMS(n, A)
>::type
operator|(Range& rng, BOOST_PP_CAT(adaptor, n)< BabyAdaptor, BOOST_PP_ENUM_PARAMS(n, A) > ad)
{
    return egg::baby_call<BabyAdaptor>( rng, BOOST_PP_ENUM(n, PSTADE_OVEN_call_arg, ~) );
}

template< class Range, class BabyAdaptor, BOOST_PP_ENUM_PARAMS(n, class A) > inline
typename egg::BOOST_PP_CAT(baby_result, BOOST_PP_INC(n))<BabyAdaptor,
    typename boost::add_const<Range>::type,
    BOOST_PP_ENUM_PARAMS(n, A)
>::type
operator|(const Range& rng, BOOST_PP_CAT(adaptor, n)< BabyAdaptor, BOOST_PP_ENUM_PARAMS(n, A) > ad)
{
    return egg::baby_call<BabyAdaptor>( rng, BOOST_PP_ENUM(n, PSTADE_OVEN_call_arg, ~) );
}


#undef n
#endif
