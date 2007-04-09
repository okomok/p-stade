#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/successors.hpp>


#include <pstade/oven/functions.hpp>


struct father_to_son
{
    template< class BaseTraversal >
    struct traversal
    {
        typedef BaseTraversal type;
    };

    template< class Iter >
    Iter increment(Iter king, Iter last) const
    {
        BOOST_CHECK(king != last);

        (void)last;
        return ++king;
    }

    template< class Iter >
    Iter decrement(Iter king, Iter last) const
    {
        (void)last;
        return --king;
    }

    template< class Diff, class Iter >
    Iter advance(Iter king, Diff d, Iter last) const
    {
        return king + d;
    }

    template< class Diff, class Iter >
    Diff difference(Iter king1, Iter king2, Iter last) const
    {
        (void)last;
        return king2 - king1;
    }
};


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    int src[] = { 1,3,5,7,9,12,3,1,2,3,4,5,6,1,2,3,23 };

    {
        std::vector<int> expected = src|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            src|successors(::father_to_son()),
            expected
        ) );

    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
