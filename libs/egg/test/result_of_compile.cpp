

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


//  Copyright Douglas Gregor 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/result_of.hpp>


#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

struct int_result_type { typedef int result_type; };

struct int_result_of
{
  template<typename F> struct result { typedef int type; };
};

struct int_result_type_and_float_result_of
{
  typedef int result_type;
  template<typename F> struct result { typedef float type; };
};

template<typename T>
struct int_result_type_template { typedef int result_type; };

template<typename T>
struct int_result_of_template
{
  template<typename F> struct result;
  template<typename This, typename That> struct result<This(That)> { typedef int type; };
};

template<typename T>
struct int_result_type_and_float_result_of_template
{
  typedef int result_type;
  template<typename F> struct result;
  template<typename This, typename That> struct result<This(That)> { typedef float type; };
};

struct X {};

int main()
{
  using boost::is_same;
  using boost::egg::result_of_;

  typedef int (*func_ptr)(float, double);
  typedef int (&func_ref)(float, double);
  typedef int (*func_ptr_0)();
  typedef int (&func_ref_0)();
  typedef int (X::*mem_func_ptr)(float);
  typedef int (X::*mem_func_ptr_c)(float) const;
  typedef int (X::*mem_func_ptr_v)(float) volatile;
  typedef int (X::*mem_func_ptr_cv)(float) const volatile;
  typedef int (X::*mem_func_ptr_0)();

  BOOST_STATIC_ASSERT((is_same<result_of_<int_result_type(float)>::type, int>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<int_result_of(double)>::type, int>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<int_result_of(void)>::type, void>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<const int_result_of(double)>::type, int>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<volatile int_result_of(void)>::type, void>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<int_result_type_and_float_result_of(char)>::type, int>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<int_result_type_template<void>(float)>::type, int>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<int_result_of_template<void>(double)>::type, int>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<int_result_of_template<void>(void)>::type, void>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<const int_result_of_template<void>(double)>::type, int>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<volatile int_result_of_template<void>(void)>::type, void>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<int_result_type_and_float_result_of_template<void>(char)>::type, int>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<func_ptr(char, float)>::type, int>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<func_ref(char, float)>::type, int>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<func_ptr_0()>::type, int>::value)); 
  BOOST_STATIC_ASSERT((is_same<result_of_<func_ref_0()>::type, int>::value)); 
#if 0
  BOOST_STATIC_ASSERT((is_same<result_of_<mem_func_ptr(X,char)>::type, int>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<mem_func_ptr_c(X,char)>::type, int>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<mem_func_ptr_v(X,char)>::type, int>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<mem_func_ptr_cv(X,char)>::type, int>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<mem_func_ptr_0(X)>::type, int>::value));
#endif

  BOOST_STATIC_ASSERT((is_same<result_of_<func_ptr(void)>::type, int>::value));

  BOOST_STATIC_ASSERT((is_same<result_of_<func_ptr const(char, float)>::type, int>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<func_ptr_0 const()>::type, int>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<func_ptr volatile(char, float)>::type, int>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<func_ptr_0 volatile()>::type, int>::value));  
  BOOST_STATIC_ASSERT((is_same<result_of_<func_ptr const volatile(char, float)>::type, int>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<func_ptr_0 const volatile()>::type, int>::value));

#if 0
//  BOOST_STATIC_ASSERT((boost::is_member_function_pointer<mem_func_ptr const>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<mem_func_ptr const(X,char)>::type, int>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<mem_func_ptr_c volatile(X,char)>::type, int>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<mem_func_ptr_v const volatile(X,char)>::type, int>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<mem_func_ptr_cv const(X,char)>::type, int>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<mem_func_ptr_0(void)>::type, int>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<mem_func_ptr_0 const(void)>::type, int>::value));
  BOOST_STATIC_ASSERT((is_same<result_of_<mem_func_ptr_0 volatile(void)>::type, int>::value));
#endif

  return 0;
}
