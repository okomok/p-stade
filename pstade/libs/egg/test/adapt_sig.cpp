#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/adapt_sig.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/egg/to_ref.hpp>
#include <string>
#include <boost/preprocessor/facilities/identity.hpp>
#include <pstade/test.hpp>
#include <pstade/result_of.hpp>
#include <boost/lambda/algorithm.hpp>
namespace ll = boost::lambda::ll;


namespace egg = pstade::egg;
using namespace egg;


typedef result_of_adapt_sig<ll::equal>::type adapted_equal;
adapted_equal const adapted_equal_fun = PSTADE_EGG_ADAPT_SIG({} BOOST_PP_EMPTY)();
PSTADE_TEST_IS_RESULT_OF((bool), adapted_equal(int*, int*, int*))


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

typedef result_of_adapt_nullary_sig< ::nullary_sig >::type adapted_nullary;
adapted_nullary const adapted_nullary_fun = PSTADE_EGG_ADAPT_SIG({} BOOST_PP_EMPTY)();
PSTADE_TEST_IS_RESULT_OF((int), adapted_nullary())


struct null_op
{
    template<class X>
    void operator()(X const&) { }
};


void pstade_minimal_test()
{
    {
        pstade::result_of<op_adapt_sig(ll::for_each)>::type adapted  = adapt_sig(ll::for_each());

        std::string s;
        adapted(s.begin()|to_ref, s.end()|to_ref, null_op()|to_ref);
        ::adapted_equal_fun(s.begin()|to_ref, s.begin()|to_ref, s.begin()|to_ref);
    }
    {
        pstade::result_of<op_adapt_nullary_sig(::nullary_sig)>::type adapted = adapt_nullary_sig(::nullary_sig());
        BOOST_CHECK( adapted() == 0 );
        int i = 0;
        BOOST_CHECK( adapted(i, i) == 2 );

        BOOST_CHECK( adapted_nullary_fun() == 0 );
        BOOST_CHECK( adapted_nullary_fun(i, i) == 2);
    }        
}
