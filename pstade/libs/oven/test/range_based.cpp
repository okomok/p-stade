#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/detail/range_based1.hpp>
#include <pstade/oven/detail/range_based2.hpp>


#include <algorithm>
#include <string>
#include <pstade/egg/less.hpp>
#include <pstade/egg/plus.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/numeric.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/algorithm.hpp>
#include <pstade/result_of_lambda.hpp>
#include <pstade/test.hpp>


struct op_sort
{
    typedef void result_type;

    template< class Iter >
    void operator()(Iter f, Iter l) const
    {
        std::sort(f, l);
    }
};

struct op_sort2
{
    typedef void result_type;

    template< class Iter, class Iter_ >
    void operator()(Iter f, Iter l, Iter_ f_, Iter_ l_) const
    {
        std::sort(f, l);
        std::sort(f_, l_);
    }
};



void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string rng("edcbagf");
        oven::detail::range_based1(::op_sort())(rng);
        BOOST_CHECK( rng == "abcdefg" );
    }
    {
        std::string rng("edcbagf");
        std::string rng_("542613");
        oven::detail::range_based2(::op_sort2())(rng, rng_);
        BOOST_CHECK( rng == "abcdefg" );
        BOOST_CHECK( rng_ == "123456" );
    }

}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
