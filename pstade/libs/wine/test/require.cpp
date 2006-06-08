#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/require.hpp>


#include <exception>
#include <iostream>


void test()
{
    using namespace pstade;

    PSTADE_REQUIRE(true);
    PSTADE_REQUIRE(false);

    PSTADE_REQUIRE_MESSAGE(true, "never see");
    PSTADE_REQUIRE_MESSAGE(false, "will see");

    bool ok = PSTADE_REQUIRE(false);
    PSTADE_REQUIRE(ok);

    if (!PSTADE_REQUIRE(true))
        BOOST_CHECK(false);

    BOOST_CHECK(
        PSTADE_REQUIRE(true)
    );

    BOOST_CHECK(
        !PSTADE_REQUIRE(false)
    );

    BOOST_CHECK(
        pstade::require(pstade::require(pstade::require(true, "never"), "see"), "this")
    );

    BOOST_CHECK(
        true | required | required | required | required
    );

    BOOST_CHECK(
        true | required("never") | required("see") | required("this") | required("message")
    );

    if (pstade::require(pstade::require(pstade::require(false))))
        BOOST_CHECK(false);

    if (pstade::require(pstade::require(pstade::require(false, "will"), "always"), "fail"))
        BOOST_CHECK(false);

    if (false | required | required | required | required)
        BOOST_CHECK(false);

    if (false | required("must") | required("be") | required("fail") | required("definitely"))
        BOOST_CHECK(false);
}


int test_main(int, char*[])
{
    try {
        ::test();
    }
    catch (std::exception& err) {
        std::cout << err.what();
    }

    return 0;
}
