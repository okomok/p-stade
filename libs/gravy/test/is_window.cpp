#include <pstade/vodka/drink.hpp>
#include <pstade/minimal_test.hpp>


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/gravy/detail/is_window.hpp>


namespace gravy = pstade::gravy;
using namespace gravy;


void pstade_minimal_test()
{
    BOOST_CHECK(detail::is_window(::GetDesktopWindow()));
    BOOST_CHECK(!detail::is_window(NULL));
}
