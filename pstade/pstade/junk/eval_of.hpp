#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EVAL_OF_HPP
#define PSTADE_EVAL_OF_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://d.hatena.ne.jp/uskz/20070409/p2#c


#include <boost/mpl/apply.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/preprocessor.hpp>


namespace pstade {


    template<class T>
    struct eval_of
    {
        typedef T type;
    };


// 0ary
    template<class Lambda>
    struct eval_of<Lambda(*)(void)> :
        boost::mpl::apply0<
            Lambda
        >
    { };

    template<class Lambda>
    struct eval_of<Lambda(void)> :
        eval_of<Lambda(*)(void)>
    { };


// 1ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_MPL_METAFUNCTION_MAX_ARITY, <pstade/eval_of.hpp>))
    #include BOOST_PP_ITERATE()


// Metafunction Classes
    #define PSTADE_fun1


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Lambda, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct eval_of<Lambda(*)(BOOST_PP_ENUM_PARAMS(n, A)> :
        boost::mpl::BOOST_PP_CAT(apply, n)<
            Lambda,
            PSTADE_PP_ENUM_PARAMS_WITH(n, typename eval_of<A, >::type)
        >
    { };

    template<class Lambda, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct eval_of<Lambda(BOOST_PP_ENUM_PARAMS(n, A)> :
        eval_of<Lambda(*)(BOOST_PP_ENUM_PARAMS(n, A))>
    { };


#undef n
#endif
