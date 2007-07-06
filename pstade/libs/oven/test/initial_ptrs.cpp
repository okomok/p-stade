#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/initial_ptrs.hpp>
#include <pstade/minimal_test.hpp>
//#define PSTADE_TEST_NONCLONABLE_NCINT
#include "./detail/test.hpp"


#include <pstade/egg/new_ptr.hpp>
#include <pstade/egg/new_auto.hpp>
#include <boost/foreach.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/detail/static_move_ptr.hpp>
#include <pstade/to_ref.hpp>


namespace oven = pstade::oven;
using namespace oven;


struct ncint2 : test::ncint
{
    ncint2(int v) : test::ncint(v)
    { }
};


result_of_initial_ptrs<test::ncint, 9>::type
make_ptrs()
{
    xp_new_auto<test::ncint> a_;
    xp_new_auto< ::ncint2 > a2_;
    return
        initial_ptrs(
            a_(3), a_(1), a2_(3), a_(6), a_(2), a2_(1), a_(7), a2_(0), a_(9)
        );
}


result_of_initial_ptrs<test::ncint, 9>::type
make_ptrs2()
{
    xp_new_auto<test::ncint> a_;
    xp_new_auto< ::ncint2 > a2_;
    pstade::egg::xp_new_ptr< boost::ptr_container_detail::static_move_ptr<test::ncint> > m_;
    return
        op_initial_ptrs< test::ncint >()(
            a2_(3), a_(1), a2_(3), a_(6), m_(2), a2_(1), a_(7), a2_(0), a_(9)
        );
}


void pstade_minimal_test()
{
    {
        int a[] = { 3,1,3,6,2,1,7,0,9 };

        boost::ptr_vector<test::ncint> rng;
        rng = *make_ptrs();

        int i = 0;
        BOOST_FOREACH (test::ncint const& x, rng) {
            BOOST_CHECK(x == a[i++]);
        }
    }
    {
        int a[] = { 3,1,3,6,2,1,7,0,9 };
        test::equality(*make_ptrs(), *test::new_vector<test::ncint>(a));
        test::equality(*make_ptrs2(), *test::new_vector<test::ncint>(a));
    }
}
