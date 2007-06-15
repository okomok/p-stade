#include <pstade/vodka/drink.hpp>
#include <pstade/minimal_test.hpp>


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/gravy/register_window_message.hpp>


#include <iostream>


PSTADE_GRAVY_REGISTER_WINDOW_MESSAGE(msg1, pstade_gravy_test_register_window_message1)
PSTADE_GRAVY_REGISTER_WINDOW_MESSAGE(msg2, pstade_gravy_test_register_window_message2)
PSTADE_GRAVY_REGISTER_WINDOW_MESSAGE(msg3, pstade_gravy_test_register_window_message3)


void pstade_minimal_test()
{
    BOOST_CHECK(msg1 != msg2);
    std::cout << msg1 << ',' << msg2 << ',' << msg3 << std::endl;
}
