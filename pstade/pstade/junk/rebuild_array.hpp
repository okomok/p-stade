#ifndef PSTADE_REBUILD_ARRAY_HPP
#define PSTADE_REBUILD_ARRAY_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#if 1 // BOOST_WORKAROUND(BOOST_MSVC, == 1310) // msvc-7.1
#include <cstddef> // size_t
#endif


namespace pstade {


#if 1 // BOOST_WORKAROUND(BOOST_MSVC, == 1310)

    namespace rebuild_array_detail {

        template<class Array>
        struct array_size
        {
            template<class T, std::size_t N>
            static char (&to_char_array(T(&)[N]))[N];

            static Array &arr;
            static int const value = sizeof(to_char_array(arr));
        };

        template<class X, class Sig = void(X)>
        struct aux
        {
            typedef X type;
        };

        template<class X, class T>
        struct aux<X, void(T[])>
        {
            typedef T type[array_size<X>::value];
        };

    } // namespace rebuild_array_detail

#endif


    template<class X>
    struct rebuild_array
    {
#if 1 // BOOST_WORKAROUND(BOOST_MSVC, == 1310)
        typedef typename rebuild_array_detail::aux<X>::type type;
#else
        typedef X type;
#endif
    };


} // namespace pstade


#endif
