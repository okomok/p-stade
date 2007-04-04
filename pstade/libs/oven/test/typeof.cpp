#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/typeof.hpp>


#include <string>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/identities.hpp>
#include <boost/typeof/typeof.hpp>


namespace oven = pstade::oven;
using namespace oven;


std::string str("abcdefg");


BOOST_TYPEOF(expression(str|identities|identities))
test_type()
{
    {
        BOOST_AUTO(r, expression(str|identities|identities));
        BOOST_CHECK( equals(r, str) );
    }

    return expression(str|identities|identities);
}


// GCC3.4 needs metafunction.
template<class Range>
struct result_of_test_template
{
    typedef BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested, expression(pstade::unknown_lvalue<Range>()|identities|identities))
    typedef typename nested::type type;
};

template<class Range>
typename ::result_of_test_template<Range>::type
test_template(Range& rng)
{
    {
        BOOST_AUTO_TPL(r, expression(rng|identities|identities));
        BOOST_CHECK( equals(r, rng) );
    }

    return expression(rng|identities|identities);
}

int test_main(int, char*[])
{
    BOOST_CHECK( equals(str, ::test_type()) );
    BOOST_CHECK( equals(str, ::test_template(str)) );
    return 0;
}
