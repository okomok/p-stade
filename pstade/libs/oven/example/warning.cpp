#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#define PSTADE_CONCEPT_CHECK
#include <pstade/oven.hpp>
#include <string>
#include <pstade/as.hpp>


using namespace pstade::oven;


int main()
{
    *begin( std::string("abc")|jointed(std::string("def")|transformed(pstade::as_value)) );
}
