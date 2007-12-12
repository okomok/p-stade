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
// Works around the bugs:
//   1. boost::result_of can't work with cv-qualified function-pointer.
//   2. boost::result_of of Boost1.34 + msvc-7.1/8.0 can't work with template pod functor.
//
// Also note that BOOST_MPL_HAS_XXX_TRAIT_DEF, which is used by boost::result_of, sometimes doesn't work.
// (Interestingly, if compiled on IDE, it seems to always work.)
// If you are lost, include <pstade/detect_result_type.hpp> before any boost header.


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/or.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/is_member_function_pointer.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/version.hpp>
#include <pstade/boost_workaround.hpp>
#include "./detail/boost_result_of.hpp"


#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) && (BOOST_VERSION < 103500)
    #include <pstade/has_xxx.hpp>
    #define PSTADE_RESULT_OF_MSVC_WORKAROUND
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


#if defined(PSTADE_RESULT_OF_MSVC_WORKAROUND)

        PSTADE_HAS_TYPE(anything)

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
            boost::mpl::eval_if<
                boost::mpl::or_< is_pointer<F>, boost::is_member_function_pointer<F> >,
                boost::remove_cv<F>,
#if defined(PSTADE_RESULT_OF_MSVC_WORKAROUND)
                msvc_identity<F>
#else
                boost::mpl::identity<F>
#endif
            >
        { };


    } // namespace result_of_detail


    // 0ary
    template<class Fun>
    struct result_of<Fun(void)> :
        boost::result_of<
            typename result_of_detail::patch<Fun>::type()
        >
    { };


    // 1ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_RESULT_OF_NUM_ARGS, <pstade/result_of.hpp>))
    #include BOOST_PP_ITERATE()


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Fun, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct result_of<Fun(BOOST_PP_ENUM_PARAMS(n, A))> :
        boost::result_of<
            typename result_of_detail::patch<Fun>::type(BOOST_PP_ENUM_PARAMS(n, A))
        >
    { };


#undef n
#endif
