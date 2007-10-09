#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/tagged.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>


namespace egg = pstade::egg;
using namespace egg;


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

T_my_foo1 const my_foo1 = PSTADE_EGG_TAGGED_L {} PSTADE_EGG_TAGGED_R;
T_my_foo2 const my_foo2 = PSTADE_EGG_TAGGED_L {} PSTADE_EGG_TAGGED_R;


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


void pstade_minimal_test()
{
    BOOST_CHECK( my_foo1(1, 2) == 3 );
    BOOST_CHECK( my_foo2(1, 2) == 3 );
}
