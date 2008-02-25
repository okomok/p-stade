

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/preprocessor/for_each_by_perfect.hpp>
#include "./egg_test.hpp"


#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/egg/preprocessor/seq_enum_params.hpp>


namespace mpl = boost::mpl;


#define MACRO(R, Int, Qs, Rs) \
    template<BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(Qs), class Arg)> \
    void foo(BOOST_EGG_PP_SEQ_ENUM_PARAMS(Rs, arg)) \
    { \
        std::string s("abc"); (void)s; \
        typedef mpl::vector<BOOST_PP_SEQ_ENUM(Qs)> qualified_t; \
        typedef mpl::vector<BOOST_PP_SEQ_ENUM(Rs)> refs_t; \
        BOOST_MPL_ASSERT((mpl::equal<refs_t, typename mpl::transform_view<qualified_t, boost::add_reference<mpl::_1> >::type>)); \
        BOOST_CHECK(arg0+arg1+arg2 == 6+7+8); \
    } \
/**/


#define MACRO_(R, Int, Qs, _) \
    template<BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(Qs), class Arg)> \
    void bar(BOOST_EGG_PP_SEQ_ENUM_PARAMS(Qs, & arg)) \
    { \
        std::string s("abc"); (void)s; \
        BOOST_CHECK(arg0+arg1+arg2 == 6+7+8); \
    } \
/**/


BOOST_EGG_PP_FOR_EACH_BY_PERFECT(3, Arg, MACRO, std::string)

BOOST_EGG_PP_FOR_EACH_BY_PERFECT(3, Arg, MACRO_, std::string)


void egg_test()
{
    {
        int i7 = 7;
        ::foo(6,i7,8);
        ::bar(6,i7,8);
    }
}
