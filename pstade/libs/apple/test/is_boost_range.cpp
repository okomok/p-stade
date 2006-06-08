#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/is_boost_range.hpp>


#include <vector>
#include <list>
#include <deque>
#include <string>
#include <map>
#include <set>
#include <boost/mpl/assert.hpp>


using namespace pstade::apple;


BOOST_MPL_ASSERT(( is_boost_range< std::vector<int> > ));
BOOST_MPL_ASSERT(( is_boost_range< std::list<int> > ));
BOOST_MPL_ASSERT(( is_boost_range< std::deque<int> > ));
BOOST_MPL_ASSERT(( is_boost_range< std::string > ));


BOOST_MPL_ASSERT_NOT(( is_boost_range< int > ));
BOOST_MPL_ASSERT_NOT(( is_boost_range< char * > ));


int test_main(int, char*[])
{
    return 0;
}
