

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


//[code_example_hello_adaptor
#include <boost/egg/lazy.hpp>
#include <boost/lambda/core.hpp>
#include <iostream>

using namespace boost::egg;

struct T_plus
{
    typedef int result_type;

    result_type operator()(int x, int y) const /*< Don't forget /const-qualifer/. >*/
    {
        return x + y;
    }
};

result_of_lazy<T_plus>::type
    const Plus = BOOST_EGG_LAZY({}); /*< Making `T_plus` __EGG_LAZY__, which can be used with __BOOST_LAMBDA__ placeholders. >*/

int main()
{
    namespace bll = boost::lambda;
    int i10 = 10;
    std::cout << Plus(bll::_1, 20)(i10); /*< Prints `30`. >*/

    return 0;
}
//]
