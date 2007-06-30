#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_RESULT_OF_HPP
#define PSTADE_RESULT_OF_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// A "lightweight" result_of which supports only function object and pointer.


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/has_xxx.hpp>


#ifndef PSTADE_RESULT_OF_MAX_ARITY
    #define PSTADE_RESULT_OF_MAX_ARITY 10
#endif


namespace pstade {


    template<class FunCall>
    struct result_of;


    namespace result_of_detail {


        template<class T>
        struct is_pointer :
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))
            boost::is_pointer<typename boost::remove_cv<T>::type>
#else
            boost::is_pointer<T>
#endif
        { };


        // function object

        PSTADE_HAS_TYPE(result_type)

        template<class Fun>
        struct result_type
        {
            typedef typename Fun::result_type type;
        };

        template<class Fun, class FunCall, int Arity>
        struct function_object_result_aux :
            Fun::template result<FunCall>
        { };

        template<class Fun, class FunCall>
        struct function_object_result_aux<Fun, FunCall, 0>
        {
            typedef void type;
        };

        template<class Fun, class FunCall, int Arity>
        struct function_object_result :
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))
            // For some reason, template pod functors need "_c".
            boost::mpl::eval_if_c< has_result_type<Fun>::value,
#else
            boost::mpl::eval_if< has_result_type<Fun>,
#endif
                result_type<Fun>,
                function_object_result_aux<Fun, FunCall, Arity>
            >
        { };


        // function pointer

        template<class Fun>
        struct function_pointer_result_aux;

        template<class Fun>
        struct function_pointer_result :
            function_pointer_result_aux<typename boost::remove_cv<Fun>::type>
        { };


    } // namespace result_of_detail


    // 0ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_RESULT_OF_MAX_ARITY, <pstade/result_of.hpp>))
    #include BOOST_PP_ITERATE()


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()

#if n == 0
    #define PSTADE_args void
#else
    #define PSTADE_args BOOST_PP_ENUM_PARAMS(n, A)
#endif


    namespace result_of_detail {

        template<class Result BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, class A)>
        struct function_pointer_result_aux<Result (*)(PSTADE_args)>
        {
            typedef Result type;
        };

    }

    template<class Fun BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, class A)>
    struct result_of<Fun(PSTADE_args)> :
        boost::mpl::eval_if< result_of_detail::is_pointer<Fun>,
            result_of_detail::function_pointer_result<Fun>,
            result_of_detail::function_object_result<Fun, Fun(PSTADE_args), n>
        >
    { };


    #undef  PSTADE_args

#undef n
#endif
