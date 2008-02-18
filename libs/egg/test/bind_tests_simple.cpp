#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


//  bind_tests_simple.cpp  -- The Boost Lambda Library ------------------
//
// Copyright (C) 2000-2003 Jaakko J�rvi (jaakko.jarvi@cs.utu.fi)
// Copyright (C) 2000-2003 Gary Powell (powellg@amazon.com)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org

// -----------------------------------------------------------------------


#include <boost/egg/bind.hpp>
#include <boost/egg/placeholders.hpp>
#include <boost/egg/pstade/minimal_test.hpp>  // see "Header Implementation Option"


namespace egg = pstade::egg;
using namespace egg;
using namespace egg::placeholders;


int sum_of_args_0() { return 0; }
int sum_of_args_1(int a) { return a; }
int sum_of_args_2(int a, int b) { return a+b; }
int sum_of_args_3(int a, int b, int c) { return a+b+c; }
int sum_of_args_4(int a, int b, int c, int d) { return a+b+c+d; }
int sum_of_args_5(int a, int b, int c, int d, int e) { return a+b+c+d+e; }
int sum_of_args_6(int a, int b, int c, int d, int e, int f) { return a+b+c+d+e+f; }
int sum_of_args_7(int a, int b, int c, int d, int e, int f, int g) { return a+b+c+d+e+f+g; }
int sum_of_args_8(int a, int b, int c, int d, int e, int f, int g, int h) { return a+b+c+d+e+f+g+h; }
int sum_of_args_9(int a, int b, int c, int d, int e, int f, int g, int h, int i) { return a+b+c+d+e+f+g+h+i; }


// ----------------------------

class A {
  int i; 
public:
  A(int n) : i(n) {};
  int add(const int& j) { return i + j; }
  int add2(int a1, int a2) { return i + a1 + a2; }
  int add3(int a1, int a2, int a3) { return i + a1 + a2 + a3; }
  int add4(int a1, int a2, int a3, int a4) { return i + a1 + a2 + a3 + a4; }
  int add5(int a1, int a2, int a3, int a4, int a5) 
  { return i + a1 + a2 + a3 + a4 + a5; }
  int add6(int a1, int a2, int a3, int a4, int a5, int a6) 
  { return i + a1 + a2 + a3 + a4 + a5 + a6; }
  int add7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) 
  { return i + a1 + a2 + a3 + a4 + a5 + a6 + a7; }
  int add8(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8) 
  { return i + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8; }

};

void test_member_functions()
{
#if 0
  using boost::ref;
  A a(10);
  int i = 1;




    BOOST_CHECK(egg::bind(&A::add, ref(a), _1)(i) == 11);
    BOOST_CHECK(egg::bind(&A::add, &a, _1)(i) == 11);
    BOOST_CHECK(egg::bind(&A::add, _1, 1)(a) == 11);
    BOOST_CHECK(egg::bind(&A::add, _1, 1)(make_const(&a)) == 11);

    BOOST_CHECK(egg::bind(&A::add2, _1, 1, 1)(a) == 12);
    BOOST_CHECK(egg::bind(&A::add3, _1, 1, 1, 1)(a) == 13);
    BOOST_CHECK(egg::bind(&A::add4, _1, 1, 1, 1, 1)(a) == 14);
    BOOST_CHECK(egg::bind(&A::add5, _1, 1, 1, 1, 1, 1)(a) == 15);
    BOOST_CHECK(egg::bind(&A::add6, _1, 1, 1, 1, 1, 1, 1)(a) == 16);
    BOOST_CHECK(egg::bind(&A::add7, _1, 1, 1, 1, 1, 1, 1, 1)(a) == 17);
    BOOST_CHECK(egg::bind(&A::add8, _1, 1, 1, 1, 1, 1, 1, 1, 1)(a) == 18);

  // This should fail, as lambda functors store arguments as const
  // egg::bind(&A::add, a, _1); 
#endif
}

void pstade_minimal_test() {

  int i = 1; int j = 2; int k = 3;
  int result;
   
  // egg::bind all parameters
#if 1
  BOOST_CHECK(egg::X_bind<int>()(&sum_of_args_0)()==0);
  BOOST_CHECK(egg::X_bind<int>()(&sum_of_args_1, 1)()==1);
  BOOST_CHECK(egg::X_bind<int>()(&sum_of_args_2, 1, 2)()==3);
  BOOST_CHECK(egg::X_bind<int>()(&sum_of_args_3, 1, 2, 3)()==6);
  BOOST_CHECK(egg::X_bind<int>()(&sum_of_args_4, 1, 2, 3, 4)()==10);
  BOOST_CHECK(egg::X_bind<int>()(&sum_of_args_5, 1, 2, 3, 4, 5)()==15);
  BOOST_CHECK(egg::X_bind<int>()(&sum_of_args_6, 1, 2, 3, 4, 5, 6)()==21);   
  BOOST_CHECK(egg::X_bind<int>()(&sum_of_args_7, 1, 2, 3, 4, 5, 6, 7)()==28);   
  BOOST_CHECK(egg::X_bind<int>()(&sum_of_args_8, 1, 2, 3, 4, 5, 6, 7, 8)()==36);   
  BOOST_CHECK(egg::X_bind<int>()(&sum_of_args_9, 1, 2, 3, 4, 5, 6, 7, 8, 9)()==45);      

  // first parameter open
  BOOST_CHECK(egg::X_bind<int>()(&sum_of_args_0)()==0);
#endif
  BOOST_CHECK(egg::bind(&sum_of_args_1, _1)(i)==1);
  BOOST_CHECK(egg::bind(&sum_of_args_2, _1, 2)(i)==3);
  BOOST_CHECK(egg::bind(&sum_of_args_3, _1, 2, 3)(i)==6);
  BOOST_CHECK(egg::bind(&sum_of_args_4, _1, 2, 3, 4)(i)==10);
  BOOST_CHECK(egg::bind(&sum_of_args_5, _1, 2, 3, 4, 5)(i)==15);
  BOOST_CHECK(egg::bind(&sum_of_args_6, _1, 2, 3, 4, 5, 6)(i)==21);   
  BOOST_CHECK(egg::bind(&sum_of_args_7, _1, 2, 3, 4, 5, 6, 7)(i)==28);   
  BOOST_CHECK(egg::bind(&sum_of_args_8, _1, 2, 3, 4, 5, 6, 7, 8)(i)==36);   
  BOOST_CHECK(egg::bind(&sum_of_args_9, _1, 2, 3, 4, 5, 6, 7, 8, 9)(i)==45);      

  // two open arguments 
#if 1
  BOOST_CHECK(egg::X_bind<int>()(&sum_of_args_0)()==0);
#endif
  BOOST_CHECK(egg::bind(&sum_of_args_1, _1)(i)==1);
  BOOST_CHECK(egg::bind(&sum_of_args_2, _1, _2)(i, j)==3);
  BOOST_CHECK(egg::bind(&sum_of_args_3, _1, _2, 3)(i, j)==6);
  BOOST_CHECK(egg::bind(&sum_of_args_4, _1, _2, 3, 4)(i, j)==10);
  BOOST_CHECK(egg::bind(&sum_of_args_5, _1, _2, 3, 4, 5)(i, j)==15);
  BOOST_CHECK(egg::bind(&sum_of_args_6, _1, _2, 3, 4, 5, 6)(i, j)==21);   
  BOOST_CHECK(egg::bind(&sum_of_args_7, _1, _2, 3, 4, 5, 6, 7)(i, j)==28);   
  BOOST_CHECK(egg::bind(&sum_of_args_8, _1, _2, 3, 4, 5, 6, 7, 8)(i, j)==36);   
  BOOST_CHECK(egg::bind(&sum_of_args_9, _1, _2, 3, 4, 5, 6, 7, 8, 9)(i, j)==45);      

  // three open arguments 
#if 1
  BOOST_CHECK(egg::X_bind<int>()(&sum_of_args_0)()==0);
#endif
  BOOST_CHECK(egg::bind(&sum_of_args_1, _1)(i)==1);
  BOOST_CHECK(egg::bind(&sum_of_args_2, _1, _2)(i, j)==3);
  BOOST_CHECK(egg::bind(&sum_of_args_3, _1, _2, _3)(i, j, k)==6);
  BOOST_CHECK(egg::bind(&sum_of_args_4, _1, _2, _3, 4)(i, j, k)==10);
  BOOST_CHECK(egg::bind(&sum_of_args_5, _1, _2, _3, 4, 5)(i, j, k)==15);
  BOOST_CHECK(egg::bind(&sum_of_args_6, _1, _2, _3, 4, 5, 6)(i, j, k)==21);   
  BOOST_CHECK(egg::bind(&sum_of_args_7, _1, _2, _3, 4, 5, 6, 7)(i, j, k)==28);   
  BOOST_CHECK(egg::bind(&sum_of_args_8, _1, _2, _3, 4, 5, 6, 7, 8)(i, j, k)==36);   
  BOOST_CHECK(egg::bind(&sum_of_args_9, _1, _2, _3, 4, 5, 6, 7, 8, 9)(i, j, k)==45);
   
  // function compositions with egg::bind
  BOOST_CHECK(egg::bind(&sum_of_args_3, egg::bind(&sum_of_args_2, _1, 2), 2, 3)(i)==8); 
#if 1
  BOOST_CHECK(
    egg::bind(&sum_of_args_9,
       egg::X_bind<int>()(&sum_of_args_0),                             // 0
       egg::bind(&sum_of_args_1, _1),                         // 1
       egg::bind(&sum_of_args_2, _1, _2),                     // 3   
       egg::bind(&sum_of_args_3, _1, _2, _3),                 // 6 
       egg::bind(&sum_of_args_4, _1, _2, _3, 4),              // 10
       egg::bind(&sum_of_args_5, _1, _2, _3, 4, 5),           // 15
       egg::bind(&sum_of_args_6, _1, _2, _3, 4, 5, 6),        // 21
       egg::bind(&sum_of_args_7, _1, _2, _3, 4, 5, 6, 7),     // 28
       egg::bind(&sum_of_args_8, _1, _2, _3, 4, 5, 6, 7, 8)   // 36
    )(i, j, k) == 120);
#endif

  // deeper nesting
  result = 
    egg::bind(&sum_of_args_1,                        // 12
       egg::bind(&sum_of_args_4,                     // 12
            egg::bind(&sum_of_args_2,                // 3
                 egg::bind(&sum_of_args_1,           // 1
                      egg::bind(&sum_of_args_1, _1)  // 1
                      ), 
                 _2),
            _2,
            _3,
            4)
     )(i, j, k);
   BOOST_CHECK(result == 12);

  test_member_functions();
}
