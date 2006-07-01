#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_UNUSED_HPP
#define PSTADE_UNUSED_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>


#if !defined(PSTADE_UNUSED_MAX_ARITY)
    #define PSTADE_UNUSED_MAX_ARITY 20
#endif


namespace pstade {


// 0ary
//
inline
void unused()
{ }


// 1ary
//
template< class A0 > inline
void unused(const A0&)
{ }


// 2ary
//
template< class A0, class A1 > inline
void unused(const A0&, const A1&)
{ }


// 3ary -
//
#define PSTADE_UNUSED_arg(Z, N, _) const BOOST_PP_CAT(A, N)&
#define BOOST_PP_ITERATION_PARAMS_1 (3, (3, PSTADE_UNUSED_MAX_ARITY, <pstade/unused.hpp>))
#include BOOST_PP_ITERATE()


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


template< BOOST_PP_ENUM_PARAMS(n, class A) > inline
void unused( BOOST_PP_ENUM(n, PSTADE_UNUSED_arg, ~) )
{ }


#undef n
#endif
