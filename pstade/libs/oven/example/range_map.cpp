#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#define PSTADE_CONCEPT_CHECK
#include <string>
#include <pstade/oven/with_data.hpp>
#include <pstade/oven/outdirected.hpp>
#include <pstade/minimal_test.hpp>
#include <pstade/oven/algorithm.hpp> // for_each


namespace oven = pstade::oven;
using namespace oven;


std::string g_str("hello");


struct T_foo
{
    template<class Iter>
    void operator()(Iter it) const
    {
        BOOST_CHECK( &oven::iter_data<std::string &>(it) == &g_str );
        BOOST_CHECK( oven::iter_data<int>(it) == 123 );
    }
};


void pstade_minimal_test()
{
    std::string &str = oven::data<std::string &>(
        g_str|with_data(boost::ref(g_str))|with_data(123)
    );
    BOOST_CHECK(&str == &g_str);

    int i = oven::data<int>(
        g_str|with_data(boost::ref(g_str))|with_data(123)
    );
    BOOST_CHECK(i == 123);

    for_each(
        g_str|with_data(boost::ref(g_str))|with_data(123)|outdirected,
        T_foo()
    );
}
