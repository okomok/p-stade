#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/curry.hpp>
#include <pstade/minimal_test.hpp>

#include <boost/ref.hpp>


struct array_size
{
    typedef int result_type;

    int operator()(int const (&)[10], int) const
    {
        return 10;
    }
};


void pstade_minimal_test()
{
    using namespace pstade::egg;

    {
        int arr[10] = {};
        BOOST_CHECK(10 == curry2(array_size())(boost::ref(arr))(999));
    }
}
