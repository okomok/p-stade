#ifndef PSTADE_EGG_DETAIL_MSVC71_ARRAY_RESURRECT_HPP
#define PSTADE_EGG_DETAIL_MSVC71_ARRAY_RESURRECT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// See http://svn.boost.org/trac/boost/ticket/1309
//
// DOESN'T WORK...


#include <cstddef> // size_t
#include <pstade/boost_workaround.hpp>
#include <pstade/has_xxx.hpp>


namespace pstade { namespace egg { namespace detail {


    PSTADE_HAS_TYPE(anything)

    template<class A, class Trick = void(A), class Trick2 = void(A)>
    struct msvc71_array_resurrect;


    template<class T, std::size_t N>
    struct make_array
    {
        typedef T (type)[N];
    };


#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    template<class A, class T, std::size_t N>
    struct msvc71_array_resurrect<A, void(T[]), void(T[N])>
    {
        typedef typename make_array<T, N+1-1>::type type;
//        static const std::size_t n = N;
 //       typedef typename make_array<T, n>::type type;
//        static const bool b = has_anything<type>::value;
    };
#endif


} } } // namespace pstade::egg::detail


#endif
