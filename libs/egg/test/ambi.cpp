

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/ambi.hpp>
#include "./egg_test.hpp"


#include <string>
#include <pstade/constant.hpp>
#include <pstade/test.hpp>


#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/egg/detail/unparen.hpp>


    #define PSTADE_AMBI(N, Object, Function) \
        namespace BOOST_PP_CAT(pstade_ambi_workarea_of_, Object) { \
            using namespace ::boost::mpl::placeholders; \
            typedef ::boost::egg::result_of< ::boost::egg::BOOST_PP_CAT(T_ambi, N)(BOOST_EGG_UNPAREN(Function)) >::type op; \
        } \
        typedef BOOST_PP_CAT(pstade_ambi_workarea_of_, Object)::op BOOST_PP_CAT(T_, Object); \
        BOOST_EGG_CONST((BOOST_PP_CAT(T_, Object)), Object) = BOOST_EGG_AMBI({}); \
    /**/


struct impl_interface0
{
    typedef std::string result_type;

    std::string operator()(std::string const& s) const
    {
        return s + "0";
    }
};

PSTADE_AMBI(0, interface0, (impl_interface0))


struct impl_interface1
{
    typedef std::string result_type;

    std::string operator()(std::string const& s, char ch1) const
    {
        return s + ch1;
    }
};

PSTADE_CONSTANT(interface1, (boost::egg::result_of<boost::egg::T_ambi1(impl_interface1)>::type))


struct impl_interface4
{
    typedef std::string result_type;

    std::string operator()(std::string const& s, char ch1, char ch2, char ch3, char ch4) const
    {
        return s + ch1 + ch2 + ch3 + ch4;
    }
};

PSTADE_CONSTANT(interface4, (boost::egg::result_of<boost::egg::T_ambi4(impl_interface4)>::type))


PSTADE_TEST_IS_RESULT_OF((std::string), T_interface0(std::string))


void egg_test()
{
    std::string s("interface");
    {
        std::string ans("interface0");
        BOOST_CHECK( interface0(s)    == ans );
        BOOST_CHECK( (s|interface0)   == ans );
        BOOST_CHECK( (s|interface0()) == ans );


        BOOST_CHECK( (interface0 |= s)    == ans );
        BOOST_CHECK( (interface0() |= s) == ans );
    }
    {
        std::string ans("interface1");
        BOOST_CHECK( interface1(s, '1')  == ans );
        BOOST_CHECK( (s|interface1('1')) == ans );

        BOOST_CHECK( (interface1('1') |= s) == ans );
    }
    {
        std::string ans("interface1234");
        BOOST_CHECK( interface4(s, '1', '2', '3', '4')  == ans );
        BOOST_CHECK( (s|interface4('1', '2', '3', '4')) == ans );

        BOOST_CHECK( (interface4('1', '2', '3', '4') |= s) == ans );
    }
}
