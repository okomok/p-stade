#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_FUNCTION_HPP
#define PSTADE_EGG_FUNCTION_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: <boost/detail/callable.hpp>
//
// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <boost/type_traits/add_const.hpp>
#include <pstade/instance.hpp>
#include <pstade/unused_to_copy.hpp>
#include "./baby_call.hpp"
#include "./baby_result.hpp"
#include "./detail/config.hpp"
#include "./detail/result_ofs.hpp"
#include "./function_fwd.hpp"


namespace pstade { namespace egg {


template< class BabyFunction >
struct function : BabyFunction
{
    typedef BabyFunction pstade_egg_baby_type;


    // 0ary
    //

    explicit function()
    { }


    typename baby_result0<BabyFunction
    >::type
    operator()(
    ) const
    {
        return egg::baby_call<BabyFunction>(*this
        );
    }


    // 1ary
    //

    template< class A0 >
    explicit function(A0& a0,
        typename unused_to_copy<function, A0>::type = 0
    ) :
        BabyFunction(a0)
    { }

    template< class A0 >
    explicit function(A0 const& a0,
        typename unused_to_copy<function, A0>::type = 0
    ) :
        BabyFunction(a0)
    { }


    template< class A0 >
    typename baby_result1<BabyFunction,
        A0
    >::type
    operator()(
        A0& a0
    ) const
    {
        return egg::baby_call<BabyFunction>(*this,
            a0
        );
    }

    template< class A0 >
    typename baby_result1<BabyFunction,
        typename boost::add_const<A0>::type
    >::type
    operator()(
        A0 const& a0
    ) const
    {
        return egg::baby_call<BabyFunction>(*this,
            a0
        );
    }


    // 2ary -
    //
    #define PSTADE_EGG_member(R, BitSeq) \
        \
        template< BOOST_PP_ENUM_PARAMS(n, class A) > \
        explicit function( \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_EGG_param, ~, BitSeq) \
        ) : \
            BabyFunction(BOOST_PP_ENUM_PARAMS(n, a)) \
        { } \
        \
        \
        template< BOOST_PP_ENUM_PARAMS(n, class A) > \
        typename BOOST_PP_CAT(baby_result, n)<BabyFunction, \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_EGG_arg_type, ~, BitSeq) \
        >::type \
        operator()( \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_EGG_param, ~, BitSeq) \
        ) const \
        { \
            return egg::baby_call<BabyFunction>(*this, \
                BOOST_PP_ENUM_PARAMS(n, a) \
            ); \
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


    #define BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_EGG_MAX_ARITY, <pstade/egg/function.hpp>))
    #include BOOST_PP_ITERATE()


    #undef PSTADE_EGG_bits
    #undef PSTADE_EGG_ac1
    #undef PSTADE_EGG_ac0
    #undef PSTADE_EGG_c1
    #undef PSTADE_EGG_c0
    #undef PSTADE_EGG_param
    #undef PSTADE_EGG_arg_type
    #undef PSTADE_EGG_member


}; // struct function


} } // namespace pstade::egg


#define PSTADE_EGG_FUNCTION(Name, Baby) \
    PSTADE_EGG_FUNCTION_define(BOOST_PP_CAT(Name, _fun), Name, Baby) \
/**/


#define PSTADE_EGG_FUNCTION_(Name, Baby) \
    PSTADE_EGG_FUNCTION_define(BOOST_PP_CAT(Name, fun), Name, Baby) \
/**/


    #define PSTADE_EGG_FUNCTION_define(TypeName, Name, Baby) \
        typedef pstade::egg::function< \
            Baby \
        > TypeName; \
        \
        PSTADE_INSTANCE( \
            pstade::egg::function< Baby > const, \
            Name, value \
        ) \
    /**/


#endif
#else
#define n BOOST_PP_ITERATION()


BOOST_PP_SEQ_FOR_EACH_PRODUCT(
    PSTADE_EGG_member,
    BOOST_PP_REPEAT(n, PSTADE_EGG_bits, ~)
)


#undef n
#endif
