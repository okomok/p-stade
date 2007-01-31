#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/regular.hpp>


#include <string>
#include <pstade/functional.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/filtered.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <pstade/new_delete.hpp>


template< class F >
void regular_check(F f)
{
    F f1(f);
    F f2;
    f2 = f1;
}


void test()
{
    namespace lambda = boost::lambda;
    namespace oven = pstade::oven;
    using namespace oven;

    {
        ::regular_check(regular(lambda::_1 != 'c'));
        ::regular_check(regular(lambda::_1 += 1 ));
        ::regular_check(shared_regular(new pstade::op_less()));
        ::regular_check(shared_regular(pstade::op_new_auto<pstade::op_less>()()));
    }
    {
        std::string rng("abcABc12c");
        std::vector<char> expected = std::string("abAB12")|copied;

        BOOST_CHECK( oven::test_Bidirectional_Readable(
            rng|filtered(regular(lambda::_1 != 'c')),
            expected
        ) );
    }
    {
        BOOST_CHECK( oven::equals(
            std::string("abcdefg")
                | filtered(regular(lambda::_1 != 'c'))
                | filtered(regular(lambda::_1 != 'f')),
            std::string("abdeg")
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
