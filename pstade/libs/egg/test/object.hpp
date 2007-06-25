#ifndef PSTADE_LIBS_EGG_TEST_OBJECT_HPP
#define PSTADE_LIBS_EGG_TEST_OBJECT_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/object.hpp>


struct fun1_
{
    typedef int result_type;

    int operator()(int) const { return 0; }
};


template<class X>
struct fun2_
{
    typedef X result_type;

    X operator()(int) const { return 'a'; }
};


PSTADE_EGG_OBJECT(fun1, (fun1_))
PSTADE_EGG_OBJECT(fun2, (fun2_<char>))


#endif
