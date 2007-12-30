#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright (C) 2000-2003 Jaakko Järvi (jaakko.jarvi@cs.utu.fi)
// Copyright (C) 2000-2003 Gary Powell (powellg@amazon.com)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org


#include <pstade/egg/bind.hpp>
#include <pstade/egg/placeholders.hpp>
#include <pstade/minimal_test.hpp>


namespace egg = pstade::egg;
using namespace egg::placeholders;


int sum_0() { return 0; }
int sum_1(int a) { return a; }
int sum_2(int a, int b) { return a+b; }

int product_2(int a, int b) { return a*b; }

// unary function that returns a pointer to a binary function
typedef int (*fptr_type)(int, int);
fptr_type sum_or_product(bool x) { 
  return x ? sum_2 : product_2; 
}

// a nullary functor that returns a pointer to a unary function that
// returns a pointer to a binary function.
struct which_one {
  typedef fptr_type (*result_type)(bool x);
  template <class T> struct sig { typedef result_type type; };

  result_type operator()() const { return sum_or_product; }
};

void test_nested_binds()
{
  int j = 2; int k = 3;

// bind calls can be nested (the target function can be a lambda functor)
// The interpretation is, that the innermost lambda functor returns something
// that is egg::bindable (another lambda functor, function pointer ...)
  bool condition;

  condition = true;
  BOOST_CHECK(egg::bind(egg::bind(&sum_or_product, _1), 1, 2)(condition)==3);
  BOOST_CHECK(egg::bind(egg::bind(&sum_or_product, _1), _2, _3)(condition, j, k)==5);

  condition = false;   
  BOOST_CHECK(egg::bind(egg::bind(&sum_or_product, _1), 1, 2)(condition)==2);
  BOOST_CHECK(egg::bind(egg::bind(&sum_or_product, _1), _2, _3)(condition, j, k)==6);


  which_one wo; 
  BOOST_CHECK(egg::bind(egg::bind(egg::bind(wo), _1), _2, _3)(condition, j, k)==6);   


  return;
}


void pstade_minimal_test()
{
    ::test_nested_binds();
}

