#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/lexical_cast.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/test.hpp>


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
        BOOST_CHECK( xp_lexical_cast<std::string>()(12) == "12" );
        std::string str = 12|lexicalize;
        BOOST_CHECK( str == "12" );
        BOOST_CHECK( xp_lexical_cast<int>()(str) == 12 );
    }

    {
        using boost::mpl::identity;
        BOOST_CHECK( xp_lexical_cast<std::string>()(12) == "12" );
        std::string str = 12|lexicalize();
        BOOST_CHECK( str == "12" );
        BOOST_CHECK( xp_lexical_cast<int>()(str) == 12 );
    }

    {
        std::string str = 12|lexicalize;
        int n = str|lexicalize;
        BOOST_CHECK( n == 12 );

        BOOST_CHECK((
            boost::lexical_cast<int, std::string>(
                egg::lexical_cast<int, std::string>(
                    12|lexicalize
                )|lexicalize
            ) == 12
        ));
    }

    ::foo(12|lexicalize);
    ::bar(12|lexicalize);

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
