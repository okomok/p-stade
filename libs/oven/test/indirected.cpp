#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK



// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/indirected.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <pstade/oven/outdirected.hpp>
#include <pstade/oven/equals.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int const a[10] = { 6,1,2,3,4,6,7,5,2,1 };
        int b_[10] = { 6,1,2,3,4,6,7,5,2,1 };
        int *b[10] = { &b_[0], &b_[1], &b_[2], &b_[3], &b_[4], &b_[5], &b_[6], &b_[7], &b_[8], &b_[9] };
        test::random_access_constant(b|indirected, a);
        test::random_access_swappable(b|indirected, a);
    }
    {
        int const a[10] = { 6,1,2,3,4,6,7,5,2,1 };
        int b_[10] = { 6,1,2,3,4,6,7,5,2,1 };
        int *b[10] = { &b_[0], &b_[1], &b_[2], &b_[3], &b_[4], &b_[5], &b_[6], &b_[7], &b_[8], &b_[9] };
        test::random_access_constant(b|test::proxies|indirected, a); // lvalue-ness resurrected
        test::random_access_swappable(b|test::proxies|indirected, a);
    }
    {
        // iter_swap extension test
        int const a[10] = { 6,1,2,3,4,6,7,5,2,1 };
        test::random_access_swappable(
            *test::new_vector<test::ncint>(a)|outdirected|indirected,
            *test::new_vector<test::ncint>(a)
        );
    }
    {
        typedef boost::shared_ptr<int> sp_t;
        sp_t p1(new int(3));
        sp_t p2(new int(3));

        std::vector<sp_t> v;
        v.push_back(p1);
        v.push_back(p2);

        BOOST_CHECK( &*boost::begin(v|indirected) == &*v[0] );
        BOOST_CHECK( &*(boost::begin(v|indirected)+1) == &*v[1] );
    }
}
