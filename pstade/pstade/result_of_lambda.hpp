#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_RESULT_OF_LAMBDA_HPP
#define PSTADE_RESULT_OF_LAMBDA_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// 20.5.4/4 (b) seems not to specify whether or not
// the specialization of 'result_of' is a legal way.
// Also, inner template specialization doesn't work well under VC++.


// Thanks to:
//
// http://d.hatena.ne.jp/uskz/20061011


#include <boost/lambda/core.hpp> // placeholders
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/utility/result_of.hpp>


namespace boost {

    // 0ary
    template< class T >
    struct result_of<boost::lambda::lambda_functor<T>(void)> :
        boost::lambda::lambda_functor<T>::template sig<
            boost::tuples::tuple<boost::lambda::lambda_functor<T>
            >
        >
    { };

    // 1ary-
    template< class T, class A0 >
    struct result_of<boost::lambda::lambda_functor<T>(A0)> :
        boost::lambda::lambda_functor<T>::template sig<
            boost::tuples::tuple<boost::lambda::lambda_functor<T>,
                // Quesion:
                // Users should add reference?
                // A Boost.Lambda functor doesn't allow rvalue as its argument,
                // so users always have to pass reference type as 'A0'? (20.5.4/1)
                typename boost::add_reference<A0>::type
            >
        >
    { };

    // 2ary-
#define PSTADE_max_arity 3 // undocumented?
#define PSTADE_add_ref(Z, N, _) typename boost::add_reference< BOOST_PP_CAT(A, N) >::type
    #define BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_max_arity, <pstade/result_of_lambda.hpp>))
    #include BOOST_PP_ITERATE()
#undef PSTADE_add_ref
#undef PSTADE_max_arity

} // namespace boost


// short typenames
//
namespace pstade {

//  typedef boost::remove_const<boost::lambda::placeholder1_type>::type _1_; // Abrahams' proposal
    typedef boost::remove_const<boost::lambda::placeholder1_type>::type lambda_1_fun;
    typedef boost::remove_const<boost::lambda::placeholder2_type>::type lambda_2_fun;
    typedef boost::remove_const<boost::lambda::placeholder3_type>::type lambda_3_fun;

} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


    template< class T, BOOST_PP_ENUM_PARAMS(n, class A) >
    struct result_of<boost::lambda::lambda_functor<T>(BOOST_PP_ENUM_PARAMS(n, A))> :
        boost::lambda::lambda_functor<T>::template sig<
            boost::tuples::tuple<boost::lambda::lambda_functor<T>,
                BOOST_PP_ENUM(n, PSTADE_add_ref, ~)
            >
        >
    { };


#undef n
#endif
