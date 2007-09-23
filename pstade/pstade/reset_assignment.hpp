#ifndef PSTADE_RESET_ASSIGNMENT_HPP
#define PSTADE_RESET_ASSIGNMENT_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/none.hpp>
#include <pstade/disable_if_copy.hpp>


#define PSTADE_RESET_ASSIGNMENT(Self) \
    template<class pstade_X> \
    typename pstade::disable_if_copy_assign<Self, pstade_X>::type \
    operator=(pstade_X &x) \
    { \
        this->reset(x); \
        return *this; \
    } \
    \
    template<class pstade_X> \
    Self & \
    operator=(pstade_X const &x) \
    { \
        this->reset(x); \
        return *this; \
    } \
    \
    Self & \
    operator=(boost::none_t) \
    { \
        this->reset(); \
        return *this; \
    } \
/**/


#define PSTADE_MOVE_RESET_ASSIGNMENT(Self) \
    template<class pstade_X> \
    typename pstade::disable_if_copy_assign<Self, pstade_X>::type \
    operator=(pstade_X x) \
    { \
        this->reset(x); \
        return *this; \
    } \
    Self & \
    operator=(boost::none_t) \
    { \
        this->reset(); \
        return *this; \
    } \
/**/


#endif
