

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/ambi.hpp>
#include "./egg_test.hpp"


#include <string>
#include <boost/egg/const.hpp>
#include "./check_is_result_of.hpp"


#include "./using_egg.hpp"


struct impl_interface0
{
    typedef std::string result_type;

    std::string operator()(std::string const& s) const
    {
        return s + "0";
    }
};

BOOST_EGG_CONST((result_of_ambi0<impl_interface0>::type), interface0) = BOOST_EGG_AMBI();


struct impl_interface1
{
    typedef std::string result_type;

    std::string operator()(std::string const& s, char ch1) const
    {
        return s + ch1;
    }
};

BOOST_EGG_CONST((result_of_ambi1<impl_interface1>::type), interface1) = BOOST_EGG_AMBI();


struct impl_interface4
{
    typedef std::string result_type;

    std::string operator()(std::string const& s, char ch1, char ch2, char ch3, char ch4) const
    {
        return s + ch1 + ch2 + ch3 + ch4;
    }
};

BOOST_EGG_CONST((result_of_ambi4<impl_interface4>::type), interface4) = BOOST_EGG_AMBI();


CHECK_IS_RESULT_OF((std::string), T_interface0(std::string))


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
