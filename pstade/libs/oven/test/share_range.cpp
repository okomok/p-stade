#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/share_range.hpp>


#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/noncopyable.hpp>
#include <pstade/new.hpp>
#include <pstade/oven/functions.hpp>


struct xxx :
    std::string,
    private boost::noncopyable
{
    explicit xxx(char const *psz) :
        std::string(psz)
    { }
};


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::string ans("0123");

    {
        std::vector<char> expected = std::string("hello, share_range")|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            new std::string("hello, share_range")|shared,
            expected
        ) );
    }
    {
        boost::shared_ptr<std::string> p(new std::string());
        make_share_iterator(p->begin(), p);
    }

    {
        BOOST_CHECK( oven::equals(oven::make_share_range(new xxx("0123")), ans) );
    }

    {
        BOOST_CHECK( oven::equals(new xxx("0123")|shared, ans) );
    }

    {
        BOOST_CHECK( oven::equals(pstade::op_new<xxx>()("0123")|shared, ans) );
    }

    {
        BOOST_FOREACH (char ch, oven::make_share_range(new xxx("0123"))) {
           std::cout << ch;
        }
    }

    {
        share_range<xxx> x1(new xxx("abc"));
        share_range<xxx> x2(new xxx("def"));
        *x1;
        x1 = x2;

        BOOST_CHECK( oven::equals(x1, std::string("def")) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
