#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Lime
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/lime.hpp>

#include <iterator>
#include <pstade/oven.hpp>
#include <pstade/wine.hpp>

using namespace pstade;

//typedef pstade::lime::node_facade<int> my_node;

struct my_node :
    lime::node_facade<my_node>
{
    typedef lime::node_facade<my_node> super_t;

    explicit my_node()
    { }

    explicit my_node(ustring name) :
        super_t(name)
    { }

    explicit my_node(my_node& parent, ustring name) :
        super_t(parent, name)
    { }
};


void test()
{
    using namespace pstade;

    ustring src("<?xml version=\"1.0\"?><parent><child>hello</child></parent>");

    ::my_node root;
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
    lime::save(root.front(), std::back_inserter(dst));
    std::cout << dst;

    BOOST_CHECK( oven::equals(dst, ans) );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
