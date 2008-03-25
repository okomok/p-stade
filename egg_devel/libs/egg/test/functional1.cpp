

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/functional1.hpp>
#include "./egg_test.hpp"


#include <memory>


void egg_test()
{
    BOOST_CHECK( boost::egg::logical_not(false) );
    BOOST_CHECK( boost::egg::negate(3) == -3 );

    std::auto_ptr<int> const p(new int(3));
    *p = 4;

#if 1
    boost::egg::dereference(p) = 4;
#endif
}
