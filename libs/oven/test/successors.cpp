#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/successors.hpp>


#include <pstade/minimal_test.hpp>
#include "./int_tests.hpp"


namespace oven = pstade::oven;
using namespace oven;


struct father_to_son
{
    template< class Iter >
    Iter operator()(Iter king, Iter last) const
    {
        BOOST_CHECK(king != last);

        (void)last;
        return ++king;
    }
};


void pstade_minimal_test()
{
    {
        int a[] = { 1,3,5,7,9,12,3,1,2,3,4,5,6,1,2,3,23 };
        int b[] = { 1,3,5,7,9,12,3,1,2,3,4,5,6,1,2,3,23 };
        PSTADE_fc(successors(::father_to_son()), a, b);
        PSTADE_fs(successors(::father_to_son()), a, b);

#if 0
        test::forward_constant (a|successors(::father_to_son()), a);
        test::forward_constant (a|const_refs|successors(::father_to_son()), a);
        test::forward_swappable(*test::new_list<int>(a)|successors(::father_to_son()), a);
        test::forward_swappable(*test::new_list<int>(a)|test::proxies|successors(::father_to_son()), a);
        test::forward_swappable(*test::new_list<test::ncint>(a)|successors(::father_to_son()), *test::new_list<test::ncint>(a));
#endif
    }
    {
        PSTADE_ef(successors(::father_to_son()));
#if 0
        test::emptiness(*test::new_list0<int>()|successors(::father_to_son()));
        test::emptiness(*test::new_list0<test::ncint>()|successors(::father_to_son()));
#endif
    }
}
