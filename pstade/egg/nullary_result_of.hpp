#ifndef PSTADE_EGG_NULLARY_RESULT_OF_HPP
#define PSTADE_EGG_NULLARY_RESULT_OF_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/preprocessor.hpp>
#include "./detail/result_of_fwd.hpp"


#define PSTADE_EGG_NULLARY_RESULT_OF_TYPE(X) \
    namespace boost { \
        \
        template< > \
        struct result_of< X(void) > \
        { \
            typedef X::nullary_result_type type; \
        }; \
        \
        template< > \
        struct result_of< X const(void) > : \
               result_of< X(void) > \
        { }; \
        \
    } \
/**/


#define PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE(X, SeqOrNum) \
    PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE_aux(X, PSTADE_PP_TO_TEMPLATE_PARAM_SEQ(SeqOrNum)) \
/**/

    #define PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE_aux(X, Seq) \
        namespace boost { \
            \
            template<PSTADE_PP_TO_TEMPLATE_PARAMS(Seq, T)> \
            struct result_of< X<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, T)>(void) > \
            { \
                typedef typename X<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, T)>::nullary_result_type type; \
            }; \
            \
            template<PSTADE_PP_TO_TEMPLATE_PARAMS(Seq, T)> \
            struct result_of< X<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, T)> const(void) > : \
                   result_of< X<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, T)>(void) > \
            { }; \
            \
         } \
    /**/


#endif
