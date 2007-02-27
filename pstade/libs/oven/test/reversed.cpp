#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#define PSTADE_OVEN_TESTS_REVERSE_RANGE_TESTING
#include <pstade/oven/tests.hpp>
#include <pstade/oven/reversed.hpp>


#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/counting.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/algorithm.hpp>
#include <pstade/oven/memoized.hpp>
#include <pstade/oven/transformed.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <pstade/locale.hpp>


template< class Range >
boost::iterator_range< boost::reverse_iterator<
    typename boost::range_result_iterator<Range>::type
> > const
make_boost_reverse(Range& rng)
{
    return boost::make_iterator_range(
        boost::make_reverse_iterator(boost::end(rng)),
        boost::make_reverse_iterator(boost::begin(rng))
    );
}


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    int src[] = { 0, 1, 2, 3, 4, 5 };
    int rev[] = { 5, 4, 3, 2, 1, 0 };

    {
        std::string rng("548175816");
        std::vector<char> expected = std::string("618571845")|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng|reversed,
            expected
        ) );
    }
    {
        BOOST_CHECK((
            oven::equals( oven::make_reversed(src), rev)
        ));
    }

    {
        BOOST_CHECK(( 5 == oven::distance(
            std::string("01234")|reversed
        ) ));
    }

    {
        BOOST_CHECK((
            oven::equals(
                src |
                    oven::reversed |
                    oven::reversed,
                src
            )
        ));
    }

    {
        BOOST_CHECK((
            oven::equals(
                src |
                    oven::reversed |
                    oven::reversed |
                    oven::reversed |
                    oven::reversed |
                    oven::reversed |
                    oven::reversed |
                    oven::reversed,
                rev
            )
        ));
    }

    {
        int const ans[] = { 5,4,3,2,1,0 };
        BOOST_CHECK((
            oven::equals(
                oven::counting(0, 6)|reversed,
                ans
            )
        ));
    }

    {
        using pstade::to_upper;
        std::string src("abcDefg");
        // oven::copy_backward(src|transformed(to_upper), boost::end(src)); can be replaced with...        
        oven::copy(src|reversed|transformed(to_upper), src|reversed|begin);
        BOOST_CHECK( oven::equals(src, std::string("ABCDEFG")) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
