#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_VC7_1_RESULT_OF_HPP
#define BOOST_EGG_DETAIL_VC7_1_RESULT_OF_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/transform.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_ARITY
#include <boost/egg/preprocessor/enum_params_with.hpp>
#include <boost/egg/preprocessor/seq_enum_i.hpp>
#include <boost/egg/preprocessor/seq_for_each_product.hpp>
#include <boost/egg/preprocessor/seq_repeat.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/detail/bytag_to.hpp>


namespace boost { namespace egg { namespace detail_vc7_1 {


    template<class Fun, BOOST_EGG_PP_ENUM_PARAMS_WITH(BOOST_EGG_MAX_ARITY, class A, = void)>
    struct result_of;


    // supports only lvalue.
    #define BOOST_EGG_spec(R, BytagSeq, Cv) \
        template<class Fun, BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(BytagSeq), class A)> \
        struct result_of<Fun, BOOST_EGG_PP_SEQ_ENUM_I_R(R, BytagSeq, BOOST_EGG_BYTAG_TO_NS_DEDUCED, ~)> : \
            result_of_<Fun(BOOST_EGG_PP_SEQ_ENUM_I_R(R, BytagSeq, BOOST_EGG_BYTAG_TO_NS_DEDUCED_REBUILT, ~))> \
        { }; \
    /**/
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_EGG_MAX_ARITY, <boost/egg/detail/vc7_1_result_of.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  BOOST_EGG_spec


} } } // namespace boost::egg::detail_vc7_1


#endif
#else
#define n BOOST_PP_ITERATION()

    BOOST_EGG_PP_SEQ_FOR_EACH_PRODUCT(
        BOOST_PP_SEQ_TRANSFORM(BOOST_EGG_BYTAG_TO_SEQ, ~, BOOST_EGG_PP_SEQ_REPEAT(by_perfect, n)), \
        BOOST_EGG_spec, ~ \
    )


#undef  n
#endif
