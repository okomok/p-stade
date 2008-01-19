#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/infix.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/egg/to_string.hpp>
#include <pstade/egg/functional.hpp> // plus
#include <string>
#include <memory>


struct str_plus_int
{
    typedef std::string result_type;

    result_type operator()(std::string s, int i) const
    {
        return s + pstade::egg::to_string(i);
    }
};

struct get_first_auto_ptr
{
    typedef std::auto_ptr<int> result_type;

    result_type operator()(std::auto_ptr<int> a, int i) const
    {
        return a;
    }
};


void pstade_minimal_test()
{
    using pstade::egg::plus;

    {
        using namespace pstade::egg::infix;

        std::string l("hello");
        int r = 12;
        BOOST_CHECK( (std::string("hello") ^str_plus_int()^ 12) == "hello12" );
        BOOST_CHECK( (l ^str_plus_int()^ 12) == "hello12" );
        BOOST_CHECK( (std::string("hello") ^str_plus_int()^ r) == "hello12" );
        BOOST_CHECK( (l ^str_plus_int()^ r) == "hello12" );
    }
    {
        using namespace pstade::egg::infix;

        int l = 10, r = 12;
        BOOST_CHECK( (10 ^plus^ 12) == 22 );
        BOOST_CHECK( (l ^plus^ 12) == 22 );
        BOOST_CHECK( (10 ^plus^ r) == 22 );
        BOOST_CHECK( (l ^plus^ r) == 22 );
    }
    {
        using namespace pstade::egg::infix_by_perfect;

        BOOST_CHECK( (10 ^plus^ 12 ^plus^ 3) == 25 );
    }

    {
        // movable check.
        using namespace pstade::egg::infix_by_value;

        std::auto_ptr<int> x(new int(3));
        std::auto_ptr<int> x_ = x ^get_first_auto_ptr()^ 10;
        (void)x_;
    }
}
