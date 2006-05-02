#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


// PStade.Lime
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/lime.hpp>


#include <pstade/oven.hpp>
#include <pstade/wine.hpp>
#include <pstade/garlic.hpp>


void test()
{
    using namespace pstade;

    ustring src("<?xml version=\"1.0\"?><parent><child>hello</child></parent>");

    lime::node<> root;
    lime::load(root, src);

    {
        try {
            root/"parent"/"child"/"grandchild";
        }
        catch (lime::node_not_found& ) {
            root/"parent"/"child" += "grandchild";
        }

        root/"parent"/"child"/"grandchild"%"age" = pstade::lexical(12);
        int i = pstade::lexical( root/"parent"/"child"/"grandchild"%"age" );
        BOOST_CHECK( i == 12 );
    }

    ustring ans("<parent><child>hello<grandchild age=\"12\"></grandchild></child></parent>");

    ustring dst;
    lime::save(root, garlic::back_inserter(dst));
    std::cout << dst;

    BOOST_CHECK( oven::equals(dst, ans) );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
