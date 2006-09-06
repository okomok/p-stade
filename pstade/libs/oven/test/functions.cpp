#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven.hpp>


#include <locale>
#include <boost/range.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <string>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <pstade/egg/function.hpp>
#include <boost/foreach.hpp>


struct is_c
{
    bool operator()(char ch) const
    { return ch == 'c'; }
};


struct baby_to_lower
{
    template< class CharT >
    struct result : boost::remove_const<CharT>
    { };

    template< class Result, class CharT >
    Result call(CharT ch)
    {
        return std::tolower(ch, std::locale());
    }
};


PSTADE_EGG_FUNCTION(to_lower, baby_to_lower)


void test()
{
    using namespace pstade;
    using namespace oven;

    std::string src1("abcde");
    std::string src2("abcde");

    { // equals
        BOOST_CHECK( oven::equals(src1, src2) );
    }

    { // distance
        BOOST_CHECK( oven::distance(src1) == 5 );
    }

    {
        using namespace boost;

        std::string out;

        BOOST_FOREACH (char ch,
            new std::string("!EXGNXXAR ,XOLXLEXH") |
                shared |
                filtered(lambda::_1 != 'X') |
                reversed |
                transformed(::to_lower)
        ) {
            out.push_back(ch);
        }

        std::cout << out;
        BOOST_CHECK( oven::equals(out, "hello, range!"|null_terminated) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
