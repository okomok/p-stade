#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/before.hpp>
#include <pstade/minimal_test.hpp>


#include <string>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <sstream>


using namespace pstade::egg;


std::stringstream g_sout;

struct thunk_
{
    void operator()() const
    {
        g_sout << "thunk_:";
    }
};

struct fun_
{
    typedef int result_type;

    int operator()(int i, int j) const
    {
        g_sout << "fun_";
        return i + j;
    }

    int operator()() const
    {
        return 0;
    }
};


void pstade_minimal_test()
{
    {
        BOOST_CHECK(before(thunk_(), fun_())(2, 5) == 7);
        BOOST_CHECK(g_sout.str() == "thunk_:fun_");
    }
    {
        BOOST_CHECK(before(thunk_(), fun_())() == 0);
    }
}
