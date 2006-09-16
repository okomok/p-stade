#ifndef PSTADE_EGG_DETAIL_CONFIG_HPP
#define PSTADE_EGG_DETAIL_CONFIG_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>


#if !defined(PSTADE_EGG_MAX_ARITY)
    #define PSTADE_EGG_MAX_ARITY 5
#endif


#define PSTADE_EGG_PIPABLE_MAX_ARITY \
    BOOST_PP_DEC(PSTADE_EGG_MAX_ARITY) \
/**/


// Note:
// The templated constructor 'function(A0& a0)'
// wins the overloading race against the implicitly generated one,
// if a 'function' object passed is not const-qualified.
// Then, if 'BabyFunction' has a templated constructor,
// a 'function' object is passed to it.
// Such behavior must be surprising, so cast it by 'static_cast'.
//

#define PSTADE_EGG_NONCOPYABLE_TO_BASE(Derived, Base) \
    Derived(Derived& other) : \
        Base(static_cast<Base&>(other)) \
    { } \
    \
    Derived(Derived const& other) : \
        Base(static_cast<Base const&>(other)) \
    { } \
    \
    Derived& operator=(Derived& other) \
    { \
        static_cast<Base&>(*this) = static_cast<Base&>(other); \
        return *this; \
    } \
    Derived& operator=(Derived const& other) \
    { \
        static_cast<Base&>(*this) = static_cast<Base const&>(other); \
        return *this; \
    } \
/**/


#endif
