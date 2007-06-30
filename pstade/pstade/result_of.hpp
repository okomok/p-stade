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


// <boost/preprocessor.hpp> is too big.
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#if !defined(BOOST_PREPROCESSOR_HPP)
    #define BOOST_PREPROCESSOR_HPP
    #include <boost/utility/result_of.hpp>
    #undef  BOOST_PREPROCESSOR_HPP
#else
    #include <boost/utility/result_of.hpp>
#endif

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/or.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/is_member_function_pointer.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/version.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) && (BOOST_VERSION < 103500)
    #include <boost/type_traits/is_class.hpp>
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
        struct force_instantiate
        {
            // For some reason, template pod functors need this.
            static bool const b = has_anything<F>::value;
            typedef F type;
        };

        template<class F>
        struct msvc_identity :
            boost::mpl::eval_if< boost::is_class<F>,
                force_instantiate<F>,
                boost::mpl::identity<F>
            >
        { };

#endif // defined(PSTADE_RESULT_OF_MSVC_WORKAROUND)


        template<class F>
        struct fix :
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
            typename result_of_detail::fix<Fun>::type()
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
            typename result_of_detail::fix<Fun>::type(BOOST_PP_ENUM_PARAMS(n, A))
        >
    { };


#undef n
#endif
