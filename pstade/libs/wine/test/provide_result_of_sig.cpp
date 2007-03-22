#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/provide_result_of_sig.hpp>


#include <pstade/test.hpp>



template<class T> struct constructor
    : pstade::provide_result_of_sig
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

PSTADE_NULLARY_RESULT_OF_SIG_TEMPLATE((constructor), 1)


struct something
    : pstade::provide_result_of_sig
{
    template<class Sig> struct sig { typedef int type; };

    int operator()() const
    {
        return 12;
    }

    int operator()(int i, int j) const
    {
        return i + j;
    }
};

PSTADE_NULLARY_RESULT_OF_SIG_TYPE((something))


PSTADE_TEST_IS_RESULT_OF((int), ::constructor<int>())
PSTADE_TEST_IS_RESULT_OF((int), ::constructor<int>(int))

PSTADE_TEST_IS_RESULT_OF((int), ::something())
PSTADE_TEST_IS_RESULT_OF((int), ::something(int, int))


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
    {
        boost::result_of< ::something()>::type result = ::something()();
        BOOST_CHECK(result == 12);
    }

    {
        int const i = 10;
        boost::result_of< ::something(int const&, int const&)>::type result = ::something()(i, i);
        BOOST_CHECK(result == 20);
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
