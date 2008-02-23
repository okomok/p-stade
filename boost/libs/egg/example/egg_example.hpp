#ifndef BOOST_LIBS_EGG_EXAMPLE_EGG_EXAMPLE_HPP
#define BOOST_LIBS_EGG_EXAMPLE_EGG_EXAMPLE_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/detail/lightweight_test.hpp>


#define BOOST_CHECK BOOST_TEST


void egg_example();


int main()
{
    egg_example();
    return boost::report_errors();
}


namespace boost { namespace egg { } }
namespace egg = boost::egg;
using namespace egg;


#endif
