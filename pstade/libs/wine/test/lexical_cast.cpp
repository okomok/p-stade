#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/lexical_cast.hpp>


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


void test()
{
    using namespace pstade;

    std::string str = pstade::lexical(12);
    BOOST_CHECK( str == "12" );

    int n = pstade::lexical(str);
    BOOST_CHECK( n == 12 );

    BOOST_CHECK((
        boost::lexical_cast<int, std::string>(
            pstade::lexical(
                boost::lexical_cast<int, std::string>(
                    pstade::lexical(12)
                )
            )
        ) == 12
    ));


    ::foo(pstade::lexical(12));
    ::bar(pstade::lexical(12));
    ::bar(12|to_lexicon);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
