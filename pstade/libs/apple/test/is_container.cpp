#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/is_container.hpp>


#include <vector>
#include <list>
#include <deque>
#include <string>
#include <map>
#include <set>
#include <boost/mpl/assert.hpp>


using namespace pstade::apple;


BOOST_MPL_ASSERT(( is_container< std::vector<int> > ));
BOOST_MPL_ASSERT(( is_container< std::list<int> > ));
BOOST_MPL_ASSERT(( is_container< std::deque<int> > ));
BOOST_MPL_ASSERT(( is_container< std::string > ));


BOOST_MPL_ASSERT_NOT(( is_container< int > ));
BOOST_MPL_ASSERT_NOT(( is_container< char * > ));


int test_main(int, char*[])
{
    return 0;
}
