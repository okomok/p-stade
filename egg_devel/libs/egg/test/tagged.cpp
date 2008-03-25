

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/tagged.hpp>
#include "./egg_test.hpp"


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>


#include "./using_egg.hpp"


struct my_foo
{
    typedef int result_type;

    int operator()(int x, int y) const
    {
        return x + y;
    }
};

struct tag1;
struct tag2;
typedef result_of_tagged<my_foo, tag1>::type T_my_foo1;
typedef result_of_tagged<my_foo, tag2>::type T_my_foo2;

T_my_foo1 const my_foo1 = BOOST_EGG_TAGGED_L {} BOOST_EGG_TAGGED_R;
T_my_foo2 const my_foo2 = BOOST_EGG_TAGGED({});


BOOST_MPL_ASSERT_NOT((is_tagged_with<my_foo, tag1>));

BOOST_MPL_ASSERT((is_tagged_with<T_my_foo1, tag1>));
BOOST_MPL_ASSERT((is_tagged_with<T_my_foo2, tag2>));
BOOST_MPL_ASSERT_NOT((is_tagged_with<T_my_foo1, tag2>));
BOOST_MPL_ASSERT_NOT((is_tagged_with<T_my_foo2, tag1>));

BOOST_MPL_ASSERT((boost::is_same<tag_of<T_my_foo1>::type, tag1>));
BOOST_MPL_ASSERT((boost::is_same<tag_of<T_my_foo2>::type, tag2>));


template<class X>
struct spec;

template<>
struct spec<T_my_foo1>
{};

template<>
struct spec<T_my_foo2>
{};


void egg_test()
{
    BOOST_CHECK( my_foo1(1, 2) == 3 );
    BOOST_CHECK( my_foo2(1, 2) == 3 );
    BOOST_CHECK( egg::tagged<tag1>(my_foo())(1, 2) == 3 );
}
