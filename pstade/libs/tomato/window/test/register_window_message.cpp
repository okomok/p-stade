#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/tomato/window/register_window_message.hpp>


PSTADE_TOMATO_REGISTER_WINDOW_MESSAGE(msg1, pstade_tomato_test_register_window_message1)
PSTADE_TOMATO_REGISTER_WINDOW_MESSAGE(msg2, pstade_tomato_test_register_window_message2)
PSTADE_TOMATO_REGISTER_WINDOW_MESSAGE(msg3, pstade_tomato_test_register_window_message3)


#include <iostream>
#include <boost/microsoft/wtl/app.hpp>
WTL::CAppModule _Module;


void test()
{
    using namespace pstade;

    BOOST_CHECK(msg1 != msg2);
    std::cout << msg1 << ',' << msg2 << ',' << msg3 << std::endl;
}


int test_main(int, char *[])
{
    ::test();
    return 0;
}
