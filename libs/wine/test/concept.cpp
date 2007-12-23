#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#define PSTADE_CONCEPT_CHECK
#undef NDEBUG
#include <pstade/concept.hpp>
#include <pstade/lightweight_test.hpp>


struct my_obj
{
    explicit my_obj(int i) {}
};


template< class Obj >
struct MyConcept
{
    PSTADE_CONCEPT_USAGE(MyConcept)
    {
    }

    Obj obj; // can be non-DefaultConstructible.
};


void pstade_lightweight_test()
{
    PSTADE_CONCEPT_ASSERT((MyConcept<my_obj>));
}

