#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/checked.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <string>
#include <boost/range.hpp>
#include <pstade/oven/algorithm.hpp>
#include <pstade/to_ref.hpp>
#include <pstade/unused.hpp>
#include <pstade/if_debug.hpp>


void pstade_minimal_test()
{
    namespace lambda = boost::lambda;
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int a[] = { 61,3,6,1,3,5,3,7,78,4,2,1,3,6 };
        int b[] = { 61,3,6,1,3,5,3,7,78,4,2,1,3,6 };
        test::adaptor_random_access_constant_int (lambda::bind(make_checked, lambda::_1), a, b);
        test::adaptor_random_access_swappable_int(lambda::bind(make_checked, lambda::_1), a, b);
    }

    {
        std::string in("012345");
        std::string out("01234");

        bool thrown = false;

        // out of range
        try {
            oven::equal( in, boost::begin(out|checked) );
        }
        catch (std::out_of_range const& ) {
            thrown = true;
        }

        BOOST_CHECK(thrown);
        thrown = false;

        (boost::begin(out|checked) + 5) - 5;

        // singular iterator
        try {
            boost::result_of<op_make_checked(std::string&)>::type srng;
            *boost::begin(srng);
        }
        catch (singular_iterator_operation const& ) {
            thrown = true;
        }

        BOOST_CHECK(thrown);
        thrown = false;

        // incompatible iterator check is not testable.
        // A good STL implementation would assert before oven's checking.
    }

    {
        pstade::unused(
            std::string()
PSTADE_IF_DEBUG(| checked)
                | pstade::to_ref,
            12
        );
    }

    {
        std::string rng("abc");
        BOOST_CHECK(*boost::begin( PSTADE_OVEN_CHECKED(rng) ) == 'a');
        test::iter_comb_sort(boost::begin(PSTADE_OVEN_CHECKED(rng)), boost::end(PSTADE_OVEN_CHECKED(rng)));
    }
}
