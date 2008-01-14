#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/cleared.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <string>


void pstade_minimal_test()
{
    namespace lambda = boost::lambda;
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string str("hello, clear_range!");
        test::emptiness(str|cleared);
        test::adaptor_emptiness_int(lambda::bind(make_cleared, lambda::_1));
    }
}
