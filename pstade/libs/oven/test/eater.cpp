#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/eater.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/output_iterator.hpp"


#include <algorithm>
#include <string>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;
    {
        std::string sin("ignored");
        std::copy(sin.begin(), sin.end(), eater());
    }
    {
        test::output_iterator(eater(), 123);
    }
}
