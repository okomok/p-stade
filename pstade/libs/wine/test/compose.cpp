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
#include <pstade/functional.hpp>


std::string g_str("x");


struct bar_fun
{
    typedef std::string& result_type;

    std::string& operator()(char) const
    {
        return g_str;
    }
};


using namespace pstade;


BOOST_MPL_ASSERT((
    boost::is_same<
        std::string&,
        boost::result_of<
            boost::result_of<
                compose_fun(identity_fun, bar_fun)
            >::type
            (char)
        >::type
    >
));


void test()
{
    {
        BOOST_CHECK( compose(identity, bar_fun())('c') == std::string("x") );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
