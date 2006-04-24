#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


#include <boost/microsoft/wtl/app.hpp>
WTL::CAppModule _Module;


// PStade.Pizza
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pizza/ini_section.hpp>
#include <pstade/pizza/reg_key.hpp>

#include <pstade/pizza/initialize.hpp>
#include <pstade/pizza/set_string.hpp>
#include <pstade/pizza/set_integer.hpp>
#include <pstade/pizza/integer.hpp>
#include <pstade/pizza/string.hpp>


#include <vector>
#include <string>
#include <sstream>
#include <pstade/oven/copy.hpp>
#include <pstade/oven/equal.hpp>
#include <pstade/tomato/tstring.hpp>


template< class Profile >
void test_profile(Profile& pr)
{
    using namespace pstade;

    pizza::initialize(pr, _T("Hello"));

    {   
        tomato::tstring data(_T("good"));
        pizza::set_string(pr, _T("Pizza"), data);
        BOOST_CHECK( oven::equals(pizza::string(pr, _T("Pizza")), data) );
    }

    {   
        unsigned int data = 123;
        pizza::set_integer(pr, _T("Bread"), data);
        BOOST_CHECK( pizza::get_integer<unsigned int>(pr, _T("Bread")) == data );

        int data_ = pizza::integer(pr, _T("Bread"));
        BOOST_CHECK( data_ == 123 );
    }

    {
        tomato::tstring ans(_T("up"));
        pizza::set_string(pr, _T("down"), ans); // down=answer
        pizza::set_string(pr, _T("left"), _T("down")); // left=down
        pizza::set_string(pr, _T("right"), _T("left")); // right=left

        BOOST_CHECK( oven::equals(ans,
            pizza::string(pr,
                pizza::string(pr, 
                    pizza::string(pr, _T("right"))
                )
            )
        ) );
    }
}


void test_ini_section()
{
    using namespace pstade;

    pizza::ini_section sec;
    ::test_profile(sec);
}


void test_reg_key()
{
    using namespace pstade;

    ATL::CRegKey key;
    ::test_profile(key);
}


int test_main(int, char*[])
{
    ::test_ini_section();
    ::test_reg_key();
    return 0;
}
