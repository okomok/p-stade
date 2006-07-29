#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/reverse_range.hpp>


#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/counting_range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/memoize_range.hpp>
#include <pstade/oven/sequence_cast.hpp>
#include <boost/iterator/reverse_iterator.hpp>


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
    using namespace pstade;
    using namespace oven;

    int src[] = { 0, 1, 2, 3, 4, 5 };
    //std::vector<int> src = oven::sequence(src_);
    int rev[] = { 5, 4, 3, 2, 1, 0 };
    //std::vector<int> rev = oven::sequence(rev_);

    {
        BOOST_CHECK((
            oven::equals( oven::make_reverse_range(src), rev)
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
                oven::zero_to(6)|reversed,
                ans
            )
        ));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
