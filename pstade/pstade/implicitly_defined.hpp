#ifndef PSTADE_IMPLICITLY_DEFINED_HPP
#define PSTADE_IMPLICITLY_DEFINED_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// 12.8/8 notes "the *copy constructor* for the class is used".
// But VC8's implicitly-defined copy-constructor can call
// any unary template constructor maybe after overload resolution.
// So is copy-assignment-operator.
// This is the fatal bug of VC8; http://tinyurl.com/yb8ban
// IIRC, VC7.1 also sometimes runs afoul of the same bug.


#include <boost/implicit_cast.hpp>
#include <pstade/boost_workaround.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))
    #define PSTADE_IMPLICITLY_DEFINED_COPY_IS_BROKEN
#endif


#if defined(PSTADE_IMPLICITLY_DEFINED_COPY_IS_BROKEN)

    #define PSTADE_IMPLICITLY_DEFINED_COPY_CONSTRUCTOR_TO_BASE(T, Base) \
        T(T const& x) : \
            Base(boost::implicit_cast<Base const&>(x)) \
        { } \
    /**/

    #define PSTADE_IMPLICITLY_DEFINED_COPY_ASSIGNMENT_TO_BASE(T, Base) \
        T& operator=(T const& x) \
        { \
            Base::operator=(boost::implicit_cast<Base const&>(x)); \
            return *this; \
        } \
    /**/

#else

    #define PSTADE_IMPLICITLY_DEFINED_COPY_CONSTRUCTOR_TO_BASE(T, Base) \
    /**/

    #define PSTADE_IMPLICITLY_DEFINED_COPY_ASSIGNMENT_TO_BASE(T, Base) \
    /**/

#endif


#define PSTADE_IMPLICITLY_DEFINED_COPY_TO_BASE(T, Base) \
    PSTADE_IMPLICITLY_DEFINED_COPY_CONSTRUCTOR_TO_BASE(T, Base) \
    PSTADE_IMPLICITLY_DEFINED_COPY_ASSIGNMENT_TO_BASE(T, Base) \
/**/


#endif
