#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_RESULT_OF_HPP
#define BOOST_EGG_RESULT_OF_HPP
#include "./detail/prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Works around the bugs:
//   1. boost::result_of can't work with cv-qualified function-pointer.
//   2. boost::result_of of Boost1.34 + msvc-7.1/8.0 can't work with template pod functor.
//
// Also note that BOOST_MPL_HAS_XXX_TRAIT_DEF, which is used by boost::result_of, sometimes doesn't work.
// (Interestingly, if compiled on IDE, it seems to always work.)
// If you are lost, include <boost/egg/detect_result_type.hpp> before any boost header.
//
// Note that member function pointers are not supported.


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/or.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/version.hpp>
#include <boost/egg/detail/boost_workaround.hpp>
#include <boost/egg/detail/in_fun_spec.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, <= 1400) && (BOOST_VERSION < 103500)
    #include <boost/egg/detail/has_xxx.hpp>
    #define BOOST_EGG_RESULT_OF_MSVC_WORKAROUND
#endif


namespace boost { namespace egg {


    template<class FunCall>
    struct result_of;


    namespace result_of_detail {


#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1500))
    // In result_of instantiation, remove_cv is needed for some reason.
    #define BOOST_EGG_RESULT_OF_IS_POINTER(T) is_pointer<typename remove_cv<T>::type>
#else
    #define BOOST_EGG_RESULT_OF_IS_POINTER(T) is_pointer<T>
#endif


#if defined(BOOST_EGG_RESULT_OF_MSVC_WORKAROUND)

        BOOST_EGG_HAS_XXX(anything)

        template<class F>
        struct msvc_identity
        {
            // For some reason, template pod functors need this.
            static bool const b = has_anything<F>::value;
            typedef F type;
        };

#endif


        template<class F>
        struct patch :
            mpl::eval_if<
                mpl::or_< BOOST_EGG_RESULT_OF_IS_POINTER(F) >,
                remove_cv<F>,
#if defined(BOOST_EGG_RESULT_OF_MSVC_WORKAROUND)
                msvc_identity<F>
#else
                mpl::identity<F>
#endif
            >
        { };


    } // namespace result_of_detail


    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_RESULT_OF_NUM_ARGS, <boost/egg/result_of.hpp>))
    #include BOOST_PP_ITERATE()


} } // namespace boost::egg


#endif
#else
#define n BOOST_PP_ITERATION()

#define fparams BOOST_EGG_PP_ENUM_PARAMS_IN_FUN_SPEC(n, A)


    template<class Fun BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
    struct result_of<Fun(fparams)> :
        boost::result_of<
            typename result_of_detail::patch<Fun>::type(fparams)
        >
    { };


#undef  fparams

#undef  n
#endif
