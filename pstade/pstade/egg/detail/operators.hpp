

// PStade.Egg
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: <boost/detail/callable.hpp>
//
// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#if !BOOST_PP_IS_ITERATING


    #ifndef PSTADE_EGG_DETAIL_OPERATORS_HPP
    #define PSTADE_EGG_DETAIL_OPERATORS_HPP


    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/preprocessor/punctuation/comma_if.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_params.hpp>
    #include <boost/preprocessor/repetition/repeat.hpp>
    #include <boost/preprocessor/seq/for_each_i.hpp>
    #include <boost/preprocessor/seq/for_each_product.hpp>
    #include <boost/type_traits/add_const.hpp>
    #include "./config.hpp" // MAX_ARITY
    #include "../baby_call.hpp"
    #include "../baby_result_type.hpp"


    namespace pstade { namespace egg { namespace detail {


    template< class BabyFunction >
    struct operators
    {

        // 0ary
        //
        typename baby_result0<BabyFunction
        >::type
        operator()(
        ) const
        {
            return egg::baby_call<BabyFunction>();
        }


        // 1ary -
        //
    #define PSTADE_EGG_call_operator(R, BitSeq) \
        template< BOOST_PP_ENUM_PARAMS(PSTADE_EGG_n, class A) > \
        typename BOOST_PP_CAT(baby_result, PSTADE_EGG_n)<BabyFunction, \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_EGG_arg_type, ~, BitSeq) \
        >::type \
        operator()( \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_EGG_param, ~, BitSeq) \
        ) const \
        { \
            return egg::baby_call<BabyFunction>( \
                BOOST_PP_ENUM_PARAMS(PSTADE_EGG_n, a) \
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


    #define PSTADE_EGG_file <pstade/egg/detail/operators.hpp>

    #define BOOST_PP_ITERATION_PARAMS_1 \
        (3, (1, PSTADE_EGG_MAX_ARITY, PSTADE_EGG_file)) \
    /**/


    #include BOOST_PP_ITERATE()


    #undef PSTADE_EGG_file
    #undef PSTADE_EGG_bits
    #undef PSTADE_EGG_ac1
    #undef PSTADE_EGG_ac0
    #undef PSTADE_EGG_c1
    #undef PSTADE_EGG_c0
    #undef PSTADE_EGG_param
    #undef PSTADE_EGG_arg_type
    #undef PSTADE_EGG_call_operator


    }; // struct operators


    } } } // namespace pstade::egg::detail


    #endif


#else


    #define PSTADE_EGG_n BOOST_PP_ITERATION()

    BOOST_PP_SEQ_FOR_EACH_PRODUCT(
        PSTADE_EGG_call_operator,
        BOOST_PP_REPEAT(PSTADE_EGG_n, PSTADE_EGG_bits, ~)
    )

    #undef PSTADE_EGG_n


#endif // !BOOST_PP_IS_ITERATING
