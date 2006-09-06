#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/is_sequence.hpp>


#include <vector>
#include <list>
#include <deque>
#include <string>
#include <map>
#include <set>
#include <boost/mpl/assert.hpp>


using namespace pstade::apple;


BOOST_MPL_ASSERT(( is_sequence< std::vector<int> > ));
BOOST_MPL_ASSERT(( is_sequence< std::list<int> > ));
BOOST_MPL_ASSERT(( is_sequence< std::deque<int> > ));
BOOST_MPL_ASSERT(( is_sequence< std::string > ));


BOOST_MPL_ASSERT_NOT(( is_sequence< int > ));
BOOST_MPL_ASSERT_NOT(( is_sequence< char * > ));
BOOST_MPL_ASSERT_NOT(( is_sequence< std::map<int, int> > ));
BOOST_MPL_ASSERT_NOT(( is_sequence< std::set<int> > ));


int test_main(int, char*[])
{
    return 0;
}
