#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../test/detail/v1_tests.hpp"


#include <string>
#include <boost/utility/result_of.hpp>
#include <pstade/locale.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/filtered.hpp>


bool is_upper(char ch)
{
    return pstade::is_upper(ch);
}


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::string src("hello, specification");

    boost::result_of<op_make_filtered(std::string&, bool(*)(char))>::type result
        = make_filtered(src, &is_upper);
    BOOST_CHECK( equals(result, src|filtered(&is_upper)) );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
