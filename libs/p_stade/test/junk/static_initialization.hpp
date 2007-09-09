#ifndef PSTADE_LIBS_EGG_STATIC_INITIALIZATION_HPP
#define PSTADE_LIBS_EGG_STATIC_INITIALIZATION_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// From Eric Niebler's example.


template<typename T>
T const & get_static_local()
{
   static const T t = T();
   return t;
}

struct S { int i; };

namespace
{
   S const & s = get_static_local<S>();
}

S const & get1();
S const & get2();


#endif

