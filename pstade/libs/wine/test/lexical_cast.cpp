#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/lexical_cast.hpp>


#include <boost/mpl/identity.hpp>


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

    {
        BOOST_CHECK( pstade::lexical_cast(12, boost::type<std::string>()) == "12" );
        std::string str = 12|lexicalized;
        BOOST_CHECK( str == "12" );
        BOOST_CHECK( pstade::lexical_cast(str, boost::type<int>()) == 12 );
    }

    {
        using boost::mpl::identity;
        BOOST_CHECK( pstade::lexical_cast(12, identity<std::string>()) == "12" );
        std::string str = 12|lexicalized;
        BOOST_CHECK( str == "12" );
        BOOST_CHECK( pstade::lexical_cast(str, identity<int>()) == 12 );
    }

    {
        std::string str = 12|lexicalized;
        int n = str|lexicalized;
        BOOST_CHECK( n == 12 );

        BOOST_CHECK((
            boost::lexical_cast<int, std::string>(
                boost::lexical_cast<int, std::string>(
                    12|lexicalized
                )|lexicalized
            ) == 12
        ));
    }

    ::foo(12|lexicalized);
    ::bar(12|lexicalized);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
