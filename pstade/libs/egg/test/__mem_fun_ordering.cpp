#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/minimal_test.hpp>


struct my
{
    void foo() const {}
    void foo() {}
    void bar() {}
};

template<class R, class T>
void take_m(R (T::*)(void)) {}

template<class R, class T>
void take_c(R (T::*)(void) const) {}

template<class R, class T>
void take_cm(R (T::*)(void)) {}

template<class R, class T>
void take_cm(R (T::*)(void) const) {}


void pstade_minimal_test()
{
    typedef void (my::*ptr_t)() const;

    ptr_t p = &my::foo;

//    ::take_m(&my::foo);
 //   ::take_c(&my::foo);
  //  ::take_cm(&my::foo);
}
