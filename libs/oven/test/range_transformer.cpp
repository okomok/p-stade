#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/range_transformer.hpp>
#include <pstade/minimal_test.hpp>


#include <algorithm>
#include <pstade/oven/equals.hpp>
#include "./detail/output_iterator.hpp"
#include <pstade/oven/regular.hpp>
#include <pstade/egg/lazy.hpp>
#include <pstade/egg/lambda/placeholders.hpp>
#include <pstade/oven/transformed.hpp>
#include <pstade/oven/filtered.hpp>
#include <vector>
#include <iterator>


struct T_my_add
{
    typedef int result_type;

    int operator()(int i) const
    {
        return i + 1;
    }
};

T_my_add const my_add = {};


struct T_is_even
{
    typedef bool result_type;

    bool operator()(int i) const
    {
        return i % 2 == 0;
    }
};

T_is_even const is_even = {};


void pstade_minimal_test()
{
    namespace bll = boost::lambda;
    namespace egg = pstade::egg;
    namespace oven = pstade::oven;
    using namespace oven;

    int const b[] = {0,1,2,3,4,5,6,7,8,9};
    int const a[] = {1,2,3,4,5,6,7,8,9,10};
    {
        int o[] = {9,8,7,6,5,4,3,2,1,0};
        std::copy(boost::begin(b), boost::end(b),
            range_transformer( regular(egg::lazy(make_transformed)(bll::_1, my_add)) ) |= &o[0]);

        BOOST_CHECK( oven::equals(o, a) );

        test::output_iterator(
            range_transformer( regular(egg::lazy(make_transformed)(bll::_1, my_add)) ) |= &o[0],
            7
        );
    }
    {
        std::vector<int> vo;
        std::copy(boost::begin(b), boost::end(b),
            range_transformer( regular(egg::lazy(make_filtered)(bll::_1, ::is_even)) ) |= std::back_inserter(vo));

        int a[] = {0,2,4,6,8};
        BOOST_CHECK( oven::equals(vo, a) );
    }
}
