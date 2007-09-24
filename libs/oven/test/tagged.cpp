#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tagged.hpp>
#include <pstade/minimal_test.hpp>


#include <string>
#include <pstade/oven/equals.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>


namespace oven = pstade::oven;
using namespace oven;


struct my_str1_tag;
struct my_str2_tag;
typedef result_of_tagged<std::string, my_str1_tag>::type my_str1;
typedef result_of_tagged<std::string, my_str2_tag>::type my_str2;


template<class X>
struct check_strong;

template<>
struct check_strong<my_str1> {};

template<>
struct check_strong<my_str2> {};


BOOST_MPL_ASSERT((boost::is_same<tag_of<my_str1>::type, my_str1_tag>));
BOOST_MPL_ASSERT((boost::is_same<tag_of<my_str2>::type, my_str2_tag>));


void pstade_minimal_test()
{

    std::string ans("f12344513215b");
    {
        my_str1 str1(ans);
        BOOST_CHECK( equals(str1, ans) );
    }
    {
        my_str2 str2(ans);
        BOOST_CHECK( equals(str2, ans) );
    }
}
