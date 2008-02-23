

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/tagged.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <functional> // multiplies


#include "./egg_example.hpp"


//[code_example_tagged
struct base_my_mult
{
    typedef int result_type;

    int operator()(int x, int y) const
    {
        return x * y;
    }
};

struct tag1;
struct tag2;
typedef result_of_tagged<std::multiplies<int>, tag1>::type T_my_mult1;
typedef result_of_tagged<std::multiplies<int>, tag2>::type T_my_mult2;

BOOST_STATIC_ASSERT(( !boost::is_same<T_my_mult1, T_my_mult2>::value ));
//]

void egg_example()
{
}
