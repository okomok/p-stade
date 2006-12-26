#ifndef PSTADE_CONST_OVERLOADED_HPP
#define PSTADE_CONST_OVERLOADED_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// GCC3.4.4 cannot order overloadings of non-const-reference and const-reference
// if it has explicit template arguments.
// So disable the non-const-reference overloading in the case of const-reference.
// http://groups.google.com/group/comp.lang.c++.moderated/browse_frm/thread/2dc6189c2eec0fd5/
// This class doesn't always do the same thing as 'disable_if<is_const<T> >'.


#include <boost/config.hpp> // BOOST_MSVC, BOOST_NO_SFINAE
#include <boost/mpl/or.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/type_traits/is_const.hpp>
#include <pstade/enable_if.hpp>


// Workaround:
// Turn it off; VC++ has problems around array types
// under weird situation even with Boost v1.34 or later.
#if defined(BOOST_MSVC) || defined(BOOST_NO_SFINAE)
    #define PSTADE_CONST_OVERLOADED_NOT_REQUIRED
#endif


namespace pstade {


    namespace const_overloaded_detail {


        template< BOOST_PP_ENUM_PARAMS(10, class T) >
        struct or10 :
            boost::mpl::or_<
                boost::mpl::or_<T0, T1, T2, T3, T4>,
                boost::mpl::or_<T5, T6, T7, T8, T9>
            >
        { };


    #define PSTADE_is_const(Z, N, _) boost::is_const< BOOST_PP_CAT(A, N) >

        template< BOOST_PP_ENUM_PARAMS(10, class A) >
        struct contains_const :
            or10< BOOST_PP_ENUM(10, PSTADE_is_const, ~) >
        { };

    #undef  PSTADE_is_const


    } // namespace const_overloaded_detail


#if !defined(PSTADE_CONST_OVERLOADED_NOT_REQUIRED)


    template<
        class A_, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(9, class A, void)
    >
    struct const_overloaded :
        disable_if<
            const_overloaded_detail::contains_const< A_, BOOST_PP_ENUM_PARAMS(9, A) >
        >
    { };


    template<
        class Result,
        class A_, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(9, class A, void)
    >
    struct const_overloaded_result :
        disable_if<
            const_overloaded_detail::contains_const< A_, BOOST_PP_ENUM_PARAMS(9, A) >,
            Result
        >
    { };


    template<
        class Result,
        class A_, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(9, class A, void)
    >
    struct const_overloaded_eval_result :
        lazy_disable_if<
            const_overloaded_detail::contains_const< A_, BOOST_PP_ENUM_PARAMS(9, A) >,
            Result
        >
    { };


#else


    template<
        class A_, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(9, class A, void)
    >
    struct const_overloaded
    {
        typedef enabler type;
    };


    template<
        class Result,
        class A_, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(9, class A, void)
    >
    struct const_overloaded_result
    {
        typedef Result type;
    };


    template<
        class Result,
        class A_, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(9, class A, void)
    >
    struct const_overloaded_eval_result
    {
        typedef typename Result::type type;
    };


#endif // !defined(PSTADE_CONST_OVERLOADED_NOT_REQUIRED)


} // namespace pstade


#endif
