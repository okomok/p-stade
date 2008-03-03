

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: http://lists.boost.org/Archives/boost/2003/10/55138.php
// Egg doesn't use boost::tuple for determining return type.


#include <boost/egg/bind.hpp>
#include "./egg_test.hpp"
#include <boost/ref.hpp>


struct a_struct
{
  virtual void f() = 0;
  virtual ~a_struct() {}
};

void f(a_struct&) {}

void egg_test()
{
    a_struct* a = 0;

    boost::egg::bind(&f, boost::ref(*a));
}
