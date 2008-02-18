#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/detail/functional1.hpp>
#include <pstade/minimal_test.hpp>


#include <memory>


void pstade_minimal_test()
{
    BOOST_CHECK( pstade::egg::logical_not(false) );
    BOOST_CHECK( pstade::egg::negate(3) == -3 );

    std::auto_ptr<int> const p(new int(3));
    *p = 4;

#if 1
    pstade::egg::dereference(p) = 4;
#endif
}
