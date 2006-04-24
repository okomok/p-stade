#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


// PStade.Napkin
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/napkin/lock_ostream.hpp>


#include <iostream>
#include <string>
#include <sstream>
#include <boost/thread/thread.hpp>


pstade::napkin::lock_ostream los;


void simple_thread()
{
    los << "lock1\n";
}


void test()
{
    using namespace pstade;

    los.reset(std::cout);

    boost::thread thrd(&simple_thread);
    los << "lock2\n";
}


int test_main(int, char*[])
{
    ::test();

    return 0;
}
