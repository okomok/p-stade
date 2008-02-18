

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/curry.hpp>
#include "./egg_test.hpp"

#include <boost/ref.hpp>


struct array_size
{
    typedef int result_type;

    int operator()(int const (&)[10], int) const
    {
        return 10;
    }
};


void egg_test()
{
    using namespace boost::egg;

    {
        int arr[10] = {};
        BOOST_CHECK(10 == curry2(array_size())(boost::ref(arr))(999));
    }
}
