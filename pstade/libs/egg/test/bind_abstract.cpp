#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: http://lists.boost.org/Archives/boost/2003/10/55138.php
// Egg doesn't use boost::tuple for determining return type.


#include <pstade/egg/bind.hpp>
#include <pstade/minimal_test.hpp>
#include <boost/ref.hpp>


struct a_struct {

  virtual void f() = 0;
};

void f(a_struct&) {}

void pstade_minimal_test()
{
    a_struct* a = 0;

    pstade::egg::bind(&f, boost::ref(*a));
}
