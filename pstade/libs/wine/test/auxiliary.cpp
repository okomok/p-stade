#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/auxiliary.hpp>


#include <string>
#include <pstade/constant.hpp>


using namespace pstade;


struct impl_interface0
{
    typedef std::string result_type;

    std::string operator()(std::string const& s) const
    {
        return s + "0";
    }
};

PSTADE_AUXILIARY0(interface0, (impl_interface0))


struct impl_interface1
{
    typedef std::string result_type;

    std::string operator()(std::string const& s, char ch1) const
    {
        return s + ch1;
    }
};

PSTADE_CONSTANT(interface1, (boost::result_of<op_auxiliary1(impl_interface1)>::type))


struct impl_interface4
{
    typedef std::string result_type;

    std::string operator()(std::string const& s, char ch1, char ch2, char ch3, char ch4) const
    {
        return s + ch1 + ch2 + ch3 + ch4;
    }
};

PSTADE_CONSTANT(interface4, (boost::result_of<op_auxiliary4(impl_interface4)>::type))



void test()
{
    std::string s("interface");
    {
        std::string ans("interface0");
        BOOST_CHECK( interface0(s)    == ans );
        BOOST_CHECK( (s|interface0)   == ans );
        BOOST_CHECK( (s|interface0()) == ans );
    }
    {
        std::string ans("interface1");
        BOOST_CHECK( interface1(s, '1')  == ans );
        BOOST_CHECK( (s|interface1('1')) == ans );
    }
    {
        std::string ans("interface1234");
        BOOST_CHECK( interface4(s, '1', '2', '3', '4')  == ans );
        BOOST_CHECK( (s|interface4('1', '2', '3', '4')) == ans );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
