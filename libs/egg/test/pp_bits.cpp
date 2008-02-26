

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/preprocessor/for_each_bits.hpp>
#include <boost/egg/preprocessor/bits_enum_binary_params.hpp>
#include <boost/egg/preprocessor/bits_enum_deduced.hpp>
#include "./egg_test.hpp"


#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/egg/preprocessor/seq_enum_params.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>


namespace mpl = boost::mpl;


#define MACRO(R, Bits, Data) \
    template<BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(Bits), class Arg)> \
    void foo(BOOST_EGG_PP_BITS_ENUM_BINARY_PARAMS_R(R, Bits, Arg, &arg)) \
    { \
        Data s("abc"); (void)s; \
        typedef mpl::vector<BOOST_EGG_PP_BITS_ENUM_DEDUCED_R(R, Bits, Arg)> qualified_t; \
        typedef mpl::vector<BOOST_EGG_PP_BITS_ENUM_BINARY_PARAMS_R(R, Bits, Arg, & BOOST_PP_INTERCEPT)> refs_t; \
        BOOST_MPL_ASSERT((mpl::equal<refs_t, typename mpl::transform_view<qualified_t, boost::add_reference<mpl::_1> >::type>)); \
        BOOST_CHECK(arg0+arg1+arg2 == 6+7+8); \
    } \
/**/

BOOST_EGG_PP_FOR_EACH_BITS(3, MACRO, std::string)


void egg_test()
{
    {
        int i7 = 7;
        ::foo(6,i7,8);
    }
}
