#ifndef PSTADE_LIGHTWEIGHT_TEST_HPP
#define PSTADE_LIGHTWEIGHT_TEST_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/detail/lightweight_test.hpp>


#define BOOST_CHECK BOOST_TEST


void pstade_lightweight_test();


int main()
{
    pstade_lightweight_test();
    return boost::report_errors();
}


#endif
