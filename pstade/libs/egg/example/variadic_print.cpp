#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)



#include <pstade/egg/variadic.hpp>
#include <pstade/minimal_test.hpp>

#include <boost/tuple/tuple.hpp>
#include <pstade/egg/bll/placeholders.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <pstade/egg/make_function.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <sstream>

namespace egg = pstade::egg;
using namespace egg;

//[code_variadic_print
std::stringstream g_out;

struct little_print
{
    template<class Me, class Args>
    struct apply
    {
        typedef void type;
    };

    template<class Re, class Args>
    void call(Args& args) const
    {
        boost::fusion::for_each(args, g_out << bll_1);
    }
};

typedef variadic<little_print>::type T_print;
T_print const print = PSTADE_EGG_VARIADIC({});

void test()
{
    print(1,'b',3,4,5);
    BOOST_CHECK(g_out.str() == "1b345");
}
//]


void pstade_minimal_test()
{
    ::test();
}
