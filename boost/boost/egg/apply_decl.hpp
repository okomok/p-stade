#ifndef BOOST_EGG_APPLY_DECL_HPP
#define BOOST_EGG_APPLY_DECL_HPP
#include "./detail/prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/egg/pstade/boost_workaround.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))
    // complete to suppress a msvc warning.
    #define BOOST_EGG_APPLY_DECL apply { }
#else
    // keep incomplete to disable SFINAE, which is C++0x result_of behavior.
    #define BOOST_EGG_APPLY_DECL apply
#endif


#define BOOST_EGG_APPLY_DECL_PARAMS(N, A) \
    class BOOST_PP_CAT(A, 0) BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(N), BOOST_EGG_APPLY_DECL_PARAMS_op, A) \
/**/

    #define BOOST_EGG_APPLY_DECL_PARAMS_op(Z, N, A) , class BOOST_PP_CAT(A, N) = void


#endif
