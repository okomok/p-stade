#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_MEM_FUN_PTR_TRAITS_HPP
#define PSTADE_EGG_DETAIL_MEM_FUN_PTR_TRAITS_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include "../config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY


namespace pstade { namespace egg { namespace detail {


    template<class MemFunPtr>
    struct mem_fun_ptr_traits_aux;


    template<class MemFunPtr>
    struct mem_fun_ptr_traits :
        mem_fun_ptr_traits_aux<typename boost::remove_cv<MemFunPtr>::type>
    { };


    // 0ary
    template<class R, class T>
    struct mem_fun_ptr_traits_aux<R (T::*)(void)>
    {
        typedef R result_type;
        typedef T class_type;
    };

    template<class R, class T>
    struct mem_fun_ptr_traits_aux<R (T::*)(void) const>
    {
        typedef R result_type;
        typedef T class_type;
    };

    template<class R, class T>
    struct mem_fun_ptr_traits_aux<R (T::*)(void) volatile>
    {
        typedef R result_type;
        typedef T class_type;
    };

    template<class R, class T>
    struct mem_fun_ptr_traits_aux<R (T::*)(void) const volatile>
    {
        typedef R result_type;
        typedef T class_type;
    };


    // 1ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/detail/mem_fun_ptr_traits.hpp>))
    #include BOOST_PP_ITERATE()


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class R, class T, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct mem_fun_ptr_traits_aux<R (T::*)(BOOST_PP_ENUM_PARAMS(n, A))>
    {
        typedef R result_type;
        typedef T class_type;
    };

    template<class R, class T, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct mem_fun_ptr_traits_aux<R (T::*)(BOOST_PP_ENUM_PARAMS(n, A)) const>
    {
        typedef R result_type;
        typedef T class_type;
    };

    template<class R, class T, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct mem_fun_ptr_traits_aux<R (T::*)(BOOST_PP_ENUM_PARAMS(n, A)) volatile>
    {
        typedef R result_type;
        typedef T class_type;
    };

    template<class R, class T, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct mem_fun_ptr_traits_aux<R (T::*)(BOOST_PP_ENUM_PARAMS(n, A)) const volatile>
    {
        typedef R result_type;
        typedef T class_type;
    };


#undef  n
#endif
