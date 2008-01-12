#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/pstade/minimal_test.hpp>

#include <ctype.h> // old header for mingw+gcc weird name lookup.
//[code_introduction
#include <boost/egg/pipable.hpp>
using namespace pstade::egg;

// This initialization incurs no runtime overhead.
result_of_pipable<int(*)(int)>::type const
    to_upper = BOOST_EGG_PIPABLE(&toupper);

void test()
{
    int maybeI = 'i'|to_upper|pipable(&tolower)|to_upper();
    BOOST_CHECK(maybeI == 'I');
}
//]

void pstade_minimal_test()
{
    ::test();
}
