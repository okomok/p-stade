#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/lexical_cast.hpp>


#include <pstade/test.hpp>


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
        BOOST_CHECK( pstade::op_lexical_cast<std::string>()(12) == "12" );
        std::string str = 12|lexicalized;
        BOOST_CHECK( str == "12" );
        BOOST_CHECK( pstade::op_lexical_cast<int>()(str) == 12 );
    }

    {
        using boost::mpl::identity;
        BOOST_CHECK( pstade::op_lexical_cast<std::string>()(12) == "12" );
        std::string str = 12|lexicalized;
        BOOST_CHECK( str == "12" );
        BOOST_CHECK( pstade::op_lexical_cast<int>()(str) == 12 );
    }

    {
        std::string str = 12|lexicalized;
        int n = str|lexicalized;
        BOOST_CHECK( n == 12 );

        BOOST_CHECK((
            boost::lexical_cast<int, std::string>(
                pstade::lexical_cast<int, std::string>(
                    12|lexicalized
                )|lexicalized
            ) == 12
        ));
    }

    ::foo(12|lexicalized);
    ::bar(12|lexicalized);

    {
        using namespace pstade;
        BOOST_CHECK(to_string(1) == std::string("1"));
        BOOST_CHECK((1|to_string) == std::string("1"));
#if defined(BOOST_MSVC)
        BOOST_CHECK((1|to_wstring) == std::wstring(L"1"));
        BOOST_CHECK(to_wstring(1) == std::wstring(L"1"));
#endif
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
