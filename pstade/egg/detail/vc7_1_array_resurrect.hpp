#ifndef PSTADE_EGG_DETAIL_VC7_1_ARRAY_RESURRECT_HPP
#define PSTADE_EGG_DETAIL_VC7_1_ARRAY_RESURRECT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Workaround for:
//
// http://svn.boost.org/trac/boost/ticket/1309
// See also <pstade/deduced_const.hpp>, which is easier workaround.


#include <pstade/boost_workaround.hpp>


#if !BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    #error This header is used only with msvc-7.1.
#endif


namespace pstade { namespace egg { namespace detail_vc7_1 {


    template<class X, class Sig = void(X)>
    struct array_resurrect_impl
    {
        typedef X type;
    };

    // A const-qualifier is stripped, but this is instantiated 
    // only in a broken context, that is to say, this array is const!
    // Note that only decayed form `T[]` can be specialized in broken context
    // so that you can get the element type.
    template<class X, class T>
    struct array_resurrect_impl< X, void(T[]) >
    {
        static X a;
        typedef T const (type)[sizeof(a)/sizeof(a[0])];
    };


    template<class X>
    struct array_resurrect :
        array_resurrect_impl<X>
    { };

    template<class T, std::size_t N>
    struct array_resurrect< T[N] >
    {
        typedef T (type)[N];
    };


} } } // namespace pstade::egg::detail_vc7_1


#endif
