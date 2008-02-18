#ifndef BOOST_LIBS_EGG_TEST_EGG_TEST_HPP
#define BOOST_LIBS_EGG_TEST_EGG_TEST_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/detail/lightweight_test.hpp>


#define BOOST_CHECK BOOST_TEST


void egg_test();


int main()
{
    egg_test();
    return boost::report_errors();
}


#endif
