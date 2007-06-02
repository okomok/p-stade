#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/compose.hpp>


#include <string>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/to_value.hpp>


std::string g_str("x");


struct bar_fun
{
    typedef std::string result_type;

    std::string operator()(char) const
    {
        return "x";
    }
};


// nullary check
int make_zero()
{
    return 0;
}

int increment(int i)
{
    return i + 1;
}


using namespace pstade;

/*
BOOST_MPL_ASSERT((
    boost::is_same<
        std::string,
        boost::result_of<
            boost::result_of<
                op_compose(op_value const, bar_fun)
            >::type
            (char)
        >::type
    >
));
*/


void test()
{
    {
        BOOST_CHECK( compose(to_value, bar_fun())('c') == std::string("x") );
    }
    {
        BOOST_CHECK( op_compose<int>()(&increment, &make_zero)() == 1 );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
