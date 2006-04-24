#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


// PStade.Napkin
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iostream>
#include <string>

#include <pstade/napkin.hpp>

struct foo_t
{
    std::string operator()(const char *psz)
    {
        std::string tmp(psz);
        return "(" + tmp + ")";
    }
};

void test_transform_out()
{
    using namespace pstade;

    std::stringstream sout;
    foo_t foo;

    napkin::ostream os1(sout);

    napkin::transform_out<foo_t> tout1(foo, os1);
    napkin::transform_out<foo_t> tout2(foo, tout1);
    napkin::transform_out<foo_t> tout3(foo, tout2);

    napkin::ostream os2(tout3);
    os2 << "hello" << "transform";

    BOOST_CHECK( sout.str() == "(((hello)))(((transform)))" );
}


int test_main(int, char*[])
{
    ::test_transform_out();

    return 0;
}
