#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OVEN_RANGE_ADAPTOR_HPP
#define PSTADE_OVEN_RANGE_ADAPTOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Why not use: 'boost::result_of'
//
// An array reference doesn't work under weird VC++7.1.


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <boost/type_traits/add_const.hpp>
#include <pstade/comma_protect.hpp>
#include <pstade/egg/baby_call.hpp>
#include <pstade/egg/baby_result_type.hpp>
#include <pstade/instance.hpp>
#include "./detail/adaptors.hpp"
#include "./detail/config.hpp" // RANGE_ADAPTOR_MAX_ARITY


namespace pstade { namespace oven {


template< class BabyAdaptor >
struct range_adaptor
{

    // structors
    //
    BabyAdaptor m_baby;

    explicit range_adaptor()
    { }

    explicit range_adaptor(BabyAdaptor baby) :
        m_baby(baby)
    { }


    // 0ary
    //
    detail_adaptors::adaptor0<BabyAdaptor>
    operator()() const
    {
        return detail_adaptors::adaptor0<BabyAdaptor
        >(m_baby);
    }


    // 1ary -
    //
    #define PSTADE_OVEN_call_operator(R, BitSeq) \
        template< BOOST_PP_ENUM_PARAMS(n, class A) > \
        detail_adaptors::BOOST_PP_CAT(adaptor, n)<BabyAdaptor, \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_OVEN_arg_type, ~, BitSeq) \
        > \
        operator()( \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_OVEN_param, ~, BitSeq) \
        ) const \
        { \
            return detail_adaptors::BOOST_PP_CAT(adaptor, n)<BabyAdaptor, \
                BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_OVEN_arg_type, ~, BitSeq) \
            >( m_baby, BOOST_PP_ENUM_PARAMS(n, a) ); \
        } \
    /**/


    #define PSTADE_OVEN_arg_type(R, _, Index, Bit) \
        BOOST_PP_COMMA_IF(Index) BOOST_PP_CAT(PSTADE_OVEN_ac, Bit)(BOOST_PP_CAT(A, Index)) \
    /**/


    #define PSTADE_OVEN_param(R, _, Index, Bit) \
        BOOST_PP_COMMA_IF(Index) \
        BOOST_PP_CAT(A, Index) BOOST_PP_CAT(PSTADE_OVEN_c, Bit) & BOOST_PP_CAT(a, Index) \
    /**/

                   
    #define PSTADE_OVEN_c0
    #define PSTADE_OVEN_c1 const


    // Workaround:
    // VC++7.1 is somewhat broken with array reference.
    #define PSTADE_OVEN_ac0(X) X
    #define PSTADE_OVEN_ac1(X) typename boost::add_const< X >::type


    #define PSTADE_OVEN_bits(Z, N, _) ((0)(1))


    #define BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_OVEN_RANGE_ADAPTOR_MAX_ARITY, <pstade/oven/range_adaptor.hpp>))
    #include BOOST_PP_ITERATE()


    #undef PSTADE_OVEN_bits
    #undef PSTADE_OVEN_ac1
    #undef PSTADE_OVEN_ac0
    #undef PSTADE_OVEN_c1
    #undef PSTADE_OVEN_c0
    #undef PSTADE_OVEN_param
    #undef PSTADE_OVEN_arg_type
    #undef PSTADE_OVEN_call_operator


}; // struct range_adaptor


// passed as is
//
template< class Range, class BabyAdaptor > inline
typename egg::baby_result1<BabyAdaptor, Range>::type
operator|(Range& rng, range_adaptor<BabyAdaptor> ad)
{
    pstade::unused(ad);
    return egg::baby_call(ad.m_baby, rng);
}

template< class Range, class BabyAdaptor > inline
typename egg::baby_result1<BabyAdaptor, typename boost::add_const<Range>::type>::type
operator|(Range const& rng, range_adaptor<BabyAdaptor> ad)
{
    pstade::unused(ad);
    return egg::baby_call(ad.m_baby, rng);
}


} } // namespace pstade::oven


#define PSTADE_OVEN_RANGE_ADAPTOR(Name, Baby) \
    PSTADE_INSTANCE( \
        pstade::oven::range_adaptor< PSTADE_COMMA_PROTECT(Baby) > const, \
        Name, value \
    ) \
/**/


#endif
#else
#define n BOOST_PP_ITERATION()


BOOST_PP_SEQ_FOR_EACH_PRODUCT(
    PSTADE_OVEN_call_operator,
    BOOST_PP_REPEAT(n, PSTADE_OVEN_bits, ~)
)


#undef n
#endif
