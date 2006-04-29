#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/adjacent_transform_range.hpp>


#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/core.hpp>
#include <boost/bind.hpp>
#include <boost/range.hpp>
#include <pstade/oven/copy.hpp>
#include <pstade/oven/equal.hpp>
#include <pstade/oven/adjacent_transform_range.hpp>
#include <pstade/oven/reverse_range.hpp>


struct is_divisor
{
    bool operator()(int x, int y) const { return (y % x) == 0; }
};

struct get_first
{
	typedef int result_type;

	template< class SubRange >
	int operator()(SubRange rng) const
	{
		return *boost::begin(rng);
	}
};

void test()
{
    using namespace pstade;
    using namespace oven;

    int src[] = { 2, 2, 4, 4, 6, 8, 8, 10, 10, 20, 40, 80, 120 };
    int ans1[] = { 2, 6, 8, 10, 120 };
    int ans2[] = { 2, 4, 6, 8, 10, 20, 40, 80, 120 };
    int ans3[] = { 2, 8, 10 };

	oven::make_adjacent_transform_iterator(boost::begin(src), boost::begin(src), boost::end(src), get_first() ,is_divisor());
	oven::make_adjacent_transform_range(src, get_first(), is_divisor());
    {
        BOOST_CHECK((
            oven::equals( oven::make_adjacent_transform_range(src, get_first(), is_divisor()), ans1)
        ));

        BOOST_CHECK((
            oven::equals( oven::make_adjacent_transform_range(src, get_first()), ans2)
        ));
        
        BOOST_CHECK((
            oven::equals( src|adjacent_transformed(get_first()), ans2 )
        ));
    }

    {
        BOOST_CHECK((
            oven::equals(
                src |
                    oven::adjacent_transformed(get_first(), is_divisor()) |
                    oven::adjacent_transformed(get_first(), is_divisor()),
                ans3
            )
        ));
    }

    {
        BOOST_CHECK((
            oven::equals( src|adjacent_transformed(get_first(), is_divisor())|reversed|reversed, ans1)
        ));

		BOOST_FOREACH (int i, src|adjacent_transformed(get_first(), is_divisor())|reversed)  {
			std::cout << i << ',';
		}
    }

	{
		using namespace boost;

		BOOST_CHECK((
			oven::equals(
				src|adjacent_transformed( boost::mem_fn(&boost::iterator_range<int*>::front) ),
				ans2
			)
		));
	}
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
