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
//
// See: http://tinyurl.com/yhqedd
//
// comp.lang.c++.moderated
// "Forwarding Function Template Resolution and Explicit Template Argument"


#include <boost/mpl/or.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/type_traits/is_const.hpp>
#include <pstade/enable_if.hpp> // disable_if


// This macro can't always be turned on; especially under VC++.
// See "/libs/wine/test/const_overloaded.cpp".
#if defined(__GNUC__)
    #define PSTADE_CONST_OVERLOADED_REQUIRED
#endif


#if defined(PSTADE_CONST_OVERLOADED_REQUIRED)

    #define PSTADE_CONST_OVERLOADED(T) \
        , typename ::pstade::disable_if< \
            ::boost::is_const<T> \
        >::type = 0 \
    /**/

    #define PSTADE_CONST_OVERLOADED_SEQ(Ts) \
        , typename ::pstade::disable_if< \
            ::pstade::const_overloaded_detail::contains_const<BOOST_PP_SEQ_ENUM(Ts)> \
        >::type = 0 \
    /**/

#else

    #define PSTADE_CONST_OVERLOADED(T)
    #define PSTADE_CONST_OVERLOADED_SEQ(Ts)

#endif


namespace pstade { namespace const_overloaded_detail {


    template<BOOST_PP_ENUM_PARAMS(10, class T)>
    struct or10 :
        boost::mpl::or_<
            boost::mpl::or_<T0, T1, T2, T3, T4>,
            boost::mpl::or_<T5, T6, T7, T8, T9>
        >
    { };


#define PSTADE_is_const(z, N, _) boost::is_const< BOOST_PP_CAT(T, N) >

    template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(10, class T, void)>
    struct contains_const :
        or10<BOOST_PP_ENUM(10, PSTADE_is_const, ~)>
    { };

#undef  PSTADE_is_const


} } // namespace pstade::const_overloaded_detail


#endif
