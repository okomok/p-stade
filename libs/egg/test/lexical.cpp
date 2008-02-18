#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/lexical.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


#include <boost/egg/pstade/test.hpp>


namespace egg = pstade::egg;
using namespace egg;


template< class T >
void foo(T& x)
{
    std::string str = x;
    BOOST_CHECK( str == "12" );
}


void bar(const std::string& str)
{
    BOOST_CHECK( str == "12" );
}


void pstade_minimal_test()
{
    {
        std::string str = lexical(12);
        BOOST_CHECK( str == "12" );
    }
    {
        BOOST_CHECK( X_lexical_cast<std::string>()(12) == "12" );
        std::string str = 12|lexical;
        BOOST_CHECK( str == "12" );
        BOOST_CHECK( X_lexical_cast<int>()(str) == 12 );
    }
    {
        using boost::mpl::identity;
        BOOST_CHECK( X_lexical_cast<std::string>()(12) == "12" );
        std::string str = 12|lexical();
        BOOST_CHECK( str == "12" );
        BOOST_CHECK( X_lexical_cast<int>()(str) == 12 );
    }

    {
        std::string str = 12|lexical;
        int n = str|lexical;
        BOOST_CHECK( n == 12 );
    }

    ::foo(12|lexical);
    ::bar(12|lexical);
}
