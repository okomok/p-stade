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
#include <pstade/result_of.hpp>
#include <pstade/egg/is_classified_as.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/filtered.hpp>


bool is_upper(char ch)
{
    return pstade::egg::is_classified_as(ch, std::ctype_base::upper);
}


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::string src("hello, specification");

    pstade::result_of<op_make_filtered(std::string&, bool(*)(char))>::type result
        = make_filtered(src, &is_upper);
    BOOST_CHECK( equals(result, src|filtered(&::is_upper)) );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
