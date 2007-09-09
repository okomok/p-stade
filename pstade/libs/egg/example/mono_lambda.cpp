#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/mono.hpp>
#include <pstade/egg/lambda/result_of.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <boost/mpl/vector.hpp>
#include <pstade/minimal_test.hpp>


namespace egg = pstade::egg;
using namespace egg;


void test()
{
    namespace bll = boost::lambda;
    namespace mpl = boost::mpl;

//[code_mono_example
int i1 = 1, i2 = 2;
BOOST_CHECK(( 3 == egg::mono< mpl::vector<int, int> >(bll::_1 + bll::_2)(i1, i2) ));

#if 0 // doesn't compile.
std::string s1("abc"), s2("def");
egg::mono< mpl::vector<int, int> >(bll::_1 + bll::_2)(s1, s2);
#endif
//]
}


void pstade_minimal_test()
{
    test();
}
