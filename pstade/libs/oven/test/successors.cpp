#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/successors.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


namespace lambda = boost::lambda;
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
        test::adaptor_forward_constant_int(
            lambda::bind(make_successors, lambda::_1, ::father_to_son()),
            a, b
        );
        test::adaptor_forward_swappable_int(
            lambda::bind(make_successors, lambda::_1, ::father_to_son()),
            a, b
        );
    }
    {
        test::adaptor_emptiness_int(
            lambda::bind(make_successors, lambda::_1, ::father_to_son())
        );
    }
}
