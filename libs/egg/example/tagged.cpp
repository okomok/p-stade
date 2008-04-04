

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
struct tag1;
struct tag2;
typedef result_of_<X_tagged<tag1>(std::multiplies<int>)>::type my_mult1;
typedef result_of_<X_tagged<tag2>(std::multiplies<int>)>::type my_mult2;

void egg_example()
{
    BOOST_CHECK( my_mult1()(3, 5) == my_mult2()(3, 5) );
    BOOST_STATIC_ASSERT(( !boost::is_same<my_mult1, my_mult2>::value ));
    BOOST_STATIC_ASSERT(( is_tagged_with<my_mult1, tag1>::value ));
}
//]
