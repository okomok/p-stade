#include <pstade/vodka/drink.hpp>
#include <pstade/minimal_test.hpp>


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/gravy/is_family_to.hpp>


#include <pstade/gravy/sdk/windows.hpp>


void pstade_minimal_test()
{
    namespace gravy = pstade::gravy;
    using namespace gravy;

    {
        BOOST_CHECK( is_family_to(::GetDesktopWindow(), ::GetDesktopWindow()) );
    }
}
