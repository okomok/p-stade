#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#define PSTADE_CONCEPT_CHECK
#include <pstade/oven/constants.hpp>
#include <string>


using namespace pstade::oven;


template< class Range >
void foo(Range const& rng)
{
    // cumbersome?
    typename pstade::result_of<op_make_constants(Range const&)>::type crng = make_constants(rng);
}


int main()
{
    std::string rng;
    ::foo(rng);
}
