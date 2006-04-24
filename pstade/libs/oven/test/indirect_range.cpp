#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/indirect_range.hpp>


#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/copy.hpp>
#include <pstade/oven/equal.hpp>


struct A
{
    void call();
};


void test()
{
    using namespace pstade;
    using namespace oven;


    char characters[] = "abcdefg";
    const int N = sizeof(characters)/sizeof(char) - 1; // -1 since characters has a null char
    char* pointers_to_chars[N];                        // at the end.
    for (int i = 0; i < N; ++i)
        pointers_to_chars[i] = &characters[i];

    char ans[] = "abcdefg";

    {
        BOOST_CHECK((
            oven::equal( oven::make_indirect_range(pointers_to_chars), ans)
        ));
    }

    {
        BOOST_CHECK((
            oven::equal(
                pointers_to_chars |
                    oven::indirected,
                ans
            )
        ));
    }

    /*
    {
        std::vector<A*> vec;
        typedef indirect_range< std::vector<A*> > rng_t;
        rng_t rng(vec);
        boost::range_result_iterator< rng_t >::type it = boost::begin(rng);
        (*it).call();
        it->call();
    }
    */
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
