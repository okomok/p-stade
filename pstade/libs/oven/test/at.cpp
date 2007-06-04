#define NDEBUG
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/at.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <string>
#include <pstade/oven/checked.hpp>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string str("f12344513215b");
        BOOST_CHECK( at(str, 0) == 'f' );
        BOOST_CHECK( at(str, 4) == '4' );
        BOOST_CHECK( (str|at(0)) == 'f' );
        BOOST_CHECK( (str|at(4)) == '4' );


        BOOST_CHECK( value_at(str, 0) == 'f' );
        BOOST_CHECK( value_at(str, 4) == '4' );
        BOOST_CHECK( (str|value_at(0)) == 'f' );
        BOOST_CHECK( (str|value_at(4)) == '4' );

        at(str, 0) = 'g';
        at(str, 4) = '5';
        BOOST_CHECK( str == "g12354513215b" );

        try {
            at(str|checked, 70);
        }
        catch(std::out_of_range) {
            return;
        }
        BOOST_CHECK(false);
    }
    {
        int rng[] = { 1,2,3,4 };
        BOOST_CHECK( &rng[0] == &(rng|at(0)) );
    }
}
