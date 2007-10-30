#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/equals.hpp>
#include <pstade/minimal_test.hpp>


#include <string>
#include <pstade/result_of.hpp>
#include <pstade/oven/identities.hpp>
#include <pstade/test.hpp>


namespace oven = pstade::oven;
using namespace oven;


PSTADE_TEST_IS_RESULT_OF((bool), T_equals(std::string&, std::string&))


struct is_a
{
    bool operator()(char ch) const
    {
        return ch == 'a';
    }
};


void pstade_minimal_test()
{
    std::string src1("abcde");
    std::string src2("abcde");
    {
        BOOST_CHECK( equals(src1, src2) );
        BOOST_CHECK( equals(src1|identities(in_single_pass), src2|identities(in_single_pass)) );
    }
}
