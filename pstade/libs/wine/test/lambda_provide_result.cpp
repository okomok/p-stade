#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/lambda_provide_result.hpp>


#include <pstade/test.hpp>



template<class T> struct constructor
    : pstade::lambda_provide_result
{
  template <class U> struct sig { typedef T type; };

  T operator()() const {
    return T();
  }

  template<class A1>
  T operator()(A1& a1) const {
    return T(a1);
  }

  template<class A1, class A2>
  T operator()(A1& a1, A2& a2) const {
    return T(a1, a2);
  }
};


PSTADE_LAMBDA_PROVIDE_NULLARY_RESULT_OF_TEMPLATE((constructor), 1)


PSTADE_TEST_IS_RESULT_OF((int), ::constructor<int>())
PSTADE_TEST_IS_RESULT_OF((int), ::constructor<int>(int))


void test()
{
    {
        boost::result_of< ::constructor<int>()>::type result = ::constructor<int>()();
        BOOST_CHECK(result == 0);
    }

    {
        int const i = 10;
        boost::result_of< ::constructor<int>(int const&)>::type result = ::constructor<int>()(i);
        BOOST_CHECK(result == 10);
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
