#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/check.hpp>


#include <iostream>


void test()
{
    using namespace pstade;

    pstade::check_reset_ostream(std::cout);

    PSTADE_CHECK(true);
    PSTADE_CHECK(false);

    PSTADE_CHECK_MESSAGE(true, "never see");
    PSTADE_CHECK_MESSAGE(false, "will see");

    bool ok = PSTADE_CHECK(false);
    PSTADE_CHECK(ok);

    if (!PSTADE_CHECK(true))
        BOOST_CHECK(false);

    BOOST_CHECK(
        PSTADE_CHECK(true)
    );

    BOOST_CHECK(
        !PSTADE_CHECK(false)
    );

    BOOST_CHECK(
        pstade::check(pstade::check(pstade::check(true, "never"), "see"), "this")
    );

    BOOST_CHECK(
        true | checked("never") | checked("see") | checked("this") | checked("message")
    );

    if (pstade::check(pstade::check(pstade::check(false, "will"), "always"), "fail"))
        BOOST_CHECK(false);

    if (false | checked("must") | checked("be") | checked("fail") | checked("definitely"))
        BOOST_CHECK(false);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
