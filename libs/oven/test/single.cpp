#include <pstade/unit_test.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/v1_tests.hpp"
#include <pstade/oven/single.hpp>
#include <pstade/oven/shared_single.hpp>


#include <memory>
#include <string>
#include <vector>
#include "./detail/v1_core.hpp"
#include <pstade/new_delete.hpp>


namespace oven = pstade::oven;
using namespace oven;


boost::result_of<op_shared_single(char *)>::type
make_rng()
{
    return shared_single(new char('a'));
}


void pstade_unit_test()
{
    std::string ans("a");

    {
        BOOST_CHECK( equals(single('a'), ans) );
    }
    {
        char ch = 'a';
        BOOST_CHECK( equals(single(ch), ans) );
    }

    {
        BOOST_CHECK( equals(shared_single(new char('a')), ans) );
    }
    {
        BOOST_CHECK( equals(::make_rng(), ans) );
    }
    {
        BOOST_CHECK( equals(shared_single(pstade::op_new_auto<char>()('a')), ans) );
    }
}

