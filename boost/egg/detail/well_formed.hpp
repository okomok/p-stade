#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_WELL_FORMED_HPP
#define BOOST_EGG_DETAIL_WELL_FORMED_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_LINEAR_ARITY
#include <boost/egg/preprocessor/enum_params_with.hpp>


namespace boost { namespace egg { namespace details {


    template<class Result>
    struct well_formed
    {
        typedef Result result_type;

    // 0ary
        result_type operator()() const;

    // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_EGG_MAX_LINEAR_ARITY, <boost/egg/detail/well_formed.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace boost::egg::details


#endif
#else
#define n BOOST_PP_ITERATION()


    template<BOOST_PP_ENUM_PARAMS(n, class A)>
    result_type operator()(BOOST_EGG_PP_ENUM_PARAMS_WITH(n, A, const &)) const;


#undef  n
#endif
