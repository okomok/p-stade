#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/to_type.hpp>


#include <boost/type.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/identity.hpp>


using namespace pstade;


BOOST_MPL_ASSERT(( boost::is_same< int, to_type< boost::type<int> >::type > ));
BOOST_MPL_ASSERT(( boost::is_same< int, to_type< boost::mpl::identity<int> >::type > ));


int test_main(int, char*[])
{
    return 0;
}
