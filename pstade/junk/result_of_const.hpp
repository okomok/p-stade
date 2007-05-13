#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_RESULT_OF_CONST_HPP
#define PSTADE_RESULT_OF_CONST_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// 'boost::result_of<const function-pointer(..)>' doesn't work.
// It seems a bug, but IMO, function behavior should not be affected by 'const'.
// Thus, this is a pending issue.


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/utility/result_of.hpp>


#define PSTADE_RESULT_OF_CONST_NEEDS_WORKAROUND


namespace pstade {


    template<class FunCall>
    struct result_of_const;


    // 0ary
    template<class Fun>
    struct result_of_const<Fun(void)> :
#if !defined(PSTADE_RESULT_OF_CONST_NEEDS_WORKAROUND)
        boost::result_of<Fun const()>
#else
        boost::result_of<Fun()>
#endif
    { };


    // 1ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_RESULT_OF_NUM_ARGS, <pstade/result_of_const.hpp>))
    #include BOOST_PP_ITERATE()


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Fun, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct result_of_const<Fun(BOOST_PP_ENUM_PARAMS(n, A))> :
#if !defined(PSTADE_RESULT_OF_CONST_NEEDS_WORKAROUND)
        boost::result_of<Fun const(BOOST_PP_ENUM_PARAMS(n, A))>
#else
        boost::result_of<Fun(BOOST_PP_ENUM_PARAMS(n, A))>
#endif
    { };


#undef n
#endif
