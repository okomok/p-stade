#ifndef PSTADE_UNUSED_HPP
#define PSTADE_UNUSED_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>


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
#define PSTADE_UNUSED_def(Z, N, _) \
    template< BOOST_PP_ENUM_PARAMS(N, class A) > inline \
    void unused( BOOST_PP_ENUM(N, PSTADE_UNUSED_arg, ~) ) \
    { } \
/**/

#define PSTADE_UNUSED_arg(Z, N, _) \
    const BOOST_PP_CAT(A, N) & \
/**/

BOOST_PP_REPEAT_FROM_TO(3, BOOST_PP_INC(PSTADE_UNUSED_MAX_ARITY), PSTADE_UNUSED_def, ~)

#undef PSTADE_UNUSED_arg
#undef PSTADE_UNUSED_def


} // namespace pstade


#endif
