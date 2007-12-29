#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/ambi.hpp>
#include <pstade/minimal_test.hpp>


#include <string>
#include <pstade/constant.hpp>
#include <pstade/test.hpp>


#include <boost/preprocessor/facilities/identity.hpp>
#include <pstade/unparenthesize.hpp>


    #define PSTADE_AMBI(N, Object, Function) \
        namespace BOOST_PP_CAT(pstade_ambi_workarea_of_, Object) { \
            using namespace ::boost::mpl::placeholders; \
            typedef ::pstade::result_of< ::pstade::egg::BOOST_PP_CAT(T_ambi, N)(PSTADE_UNPARENTHESIZE(Function)) >::type op; \
        } \
        typedef BOOST_PP_CAT(pstade_ambi_workarea_of_, Object)::op BOOST_PP_CAT(T_, Object); \
        PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_, Object)), Object) = PSTADE_EGG_AMBI({}); \
    /**/


struct impl_interface1
{
    typedef std::string result_type;

    std::string operator()(std::string const& s) const
    {
        return s + "1";
    }
};

PSTADE_AMBI(1, interface1, (impl_interface1))


struct impl_interface2
{
    typedef std::string result_type;

    std::string operator()(std::string const& s, char ch1) const
    {
        return s + ch1;
    }
};

PSTADE_CONSTANT(interface2, (pstade::result_of<pstade::egg::T_ambi2(impl_interface2)>::type))


struct impl_interface5
{
    typedef std::string result_type;

    std::string operator()(std::string const& s, char ch1, char ch2, char ch3, char ch4) const
    {
        return s + ch1 + ch2 + ch3 + ch4;
    }
};

PSTADE_CONSTANT(interface5, (pstade::result_of<pstade::egg::T_ambi5(impl_interface5)>::type))


PSTADE_TEST_IS_RESULT_OF((std::string), T_interface1(std::string))


void pstade_minimal_test()
{
    std::string s("interface");
    {
        std::string ans("interface1");
        BOOST_CHECK( interface1(s)    == ans );
        BOOST_CHECK( (s|interface1)   == ans );
        BOOST_CHECK( (s|interface1()) == ans );


        BOOST_CHECK( (interface1 |= s)    == ans );
        BOOST_CHECK( (interface1() |= s) == ans );
    }
    {
        std::string ans("interface2");
        BOOST_CHECK( interface2(s, '2')  == ans );
        BOOST_CHECK( (s|interface2('2')) == ans );

        BOOST_CHECK( (interface2('2') |= s) == ans );
    }
    {
        std::string ans("interface1234");
        BOOST_CHECK( interface5(s, '1', '2', '3', '4')  == ans );
        BOOST_CHECK( (s|interface5('1', '2', '3', '4')) == ans );

        BOOST_CHECK( (interface5('1', '2', '3', '4') |= s) == ans );
    }
}
