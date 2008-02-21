

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/bll/poly.hpp>
#include "./egg_test.hpp"


#include <boost/egg/to_ref.hpp>
#include <string>
#include <boost/preprocessor/facilities/identity.hpp>
#include "./check_is_result_of.hpp"
#include <boost/egg/result_of.hpp>
#include <boost/lambda/algorithm.hpp>
namespace ll = boost::lambda::ll;


#include "./using_egg.hpp"


typedef result_of_bll_poly<ll::equal>::type adapted_equal;
adapted_equal const adapted_equal_fun = BOOST_EGG_BLL_POLY({});
CHECK_IS_RESULT_OF(bool, adapted_equal(int*, int*, int*))


struct nullary_sig
{
  template <class Args>
  struct sig { 
    typedef int type;
  };

  template <class A >
  int operator()(A a, A b) const
  { return 2; }

  int operator()() const
  { return 0; }
};

typedef result_of_bll_poly_nullary< ::nullary_sig >::type adapted_nullary;
adapted_nullary const adapted_nullary_fun = BOOST_EGG_BLL_POLY_L {} BOOST_EGG_BLL_POLY_R;
CHECK_IS_RESULT_OF(int, adapted_nullary())


struct null_op
{
    template<class X>
    void operator()(X const&) { }
};


void egg_test()
{
    {
        boost::egg::result_of_<T_bll_poly(ll::for_each)>::type adapted  = bll_poly(ll::for_each());

        std::string s;
        adapted(s.begin()|to_ref, s.end()|to_ref, null_op()|to_ref);
        ::adapted_equal_fun(s.begin()|to_ref, s.begin()|to_ref, s.begin()|to_ref);
    }
    {
        boost::egg::result_of_<T_bll_poly_nullary(::nullary_sig)>::type adapted = bll_poly_nullary(::nullary_sig());
        BOOST_CHECK( adapted() == 0 );
        int i = 0;
        BOOST_CHECK( adapted(i, i) == 2 );

        BOOST_CHECK( adapted_nullary_fun() == 0 );
        BOOST_CHECK( adapted_nullary_fun(i, i) == 2);
    }        
}
