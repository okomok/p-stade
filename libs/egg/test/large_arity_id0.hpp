#ifndef PSTADE_LIBS_EGG_TEST_LARGE_ARITY_ID0_HPP
#define PSTADE_LIBS_EGG_TEST_LARGE_ARITY_ID0_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)



// inclusion guaranteed
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/by_ref.hpp>
#include <boost/egg/by_cref.hpp>
#include <boost/egg/by_value.hpp>


struct T_large_arity_id0
{
    template<class Signature>
    struct result;

    template<class Self, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    struct result<Self(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9)>
    {
        typedef typename boost::egg::details::unref<boost::egg::by_perfect, A0>::type &type;
    };

    template<class A0>
    A0& operator()(A0& a0, ...) const
    {
        return a0;
    }
};

T_large_arity_id0 const large_arity_id0 = {};


namespace {

    namespace large_arity_helpers {
        int i0 = 0, i1 = 1, i2 = 2, i3 = 3, i4 = 4, i5 = 5, i6 = 6, i7 = 7, i8 = 8, i9 = 9;
        int const ci0 = 0, ci1 = 1, ci2 = 2, ci3 = 3, ci4 = 4, ci5 = 5, ci6 = 6, ci7 = 7, ci8 = 8, ci9 = 9;
    }

}


#endif
