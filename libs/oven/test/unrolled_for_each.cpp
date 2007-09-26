#define _SECURE_SCL 0
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or for_each at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/unrolled_for_each.hpp>
#include <pstade/minimal_test.hpp>


#include <vector>
#include <pstade/oven/copied.hpp>
#include <string>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/algorithm.hpp>
#include <boost/progress.hpp>


namespace oven = pstade::oven;
using namespace oven;


template<class Container>
struct op_push_back
{
    template<class V>
    void operator()(V const& v)
    {
        m_c.push_back(v);
    }

    Container& m_c;
};

template<class Container>
op_push_back<Container> push_backer(Container& c)
{
    op_push_back<Container> r = {c};
    return r;
}



void pstade_minimal_test()
{
    int const count = 1000; // 100000000;
    {
        std::vector<char> b = std::string("abcdefg")|copied;
        std::vector<char> a;
        {
            boost::progress_timer t;
            for (int i = 0; i < count; ++i) {
                a.resize(0);
                oven::unrolled_for_each< boost::mpl::int_<7> >(b, ::push_backer(a));
            }
        }
        BOOST_CHECK( equals(a, b) );
    }
    {
        std::vector<char> b = std::string("abcdefg")|copied;
        std::vector<char> a;
        {
            boost::progress_timer t;
            for (int i = 0; i < count; ++i) {
                a.resize(0);
                oven::for_each(b, ::push_backer(a));
            }
        }
        BOOST_CHECK( equals(a, b) );
    }

    {
        std::string b = "abcdefg";
        std::string a;
        {
            boost::progress_timer t;
            for (int i = 0; i < count; ++i) {
                a.resize(0);
                oven::unrolled_for_each_c<7>(b, ::push_backer(a));
            }
        }
        BOOST_CHECK( equals(a, b) );
    }
    {
        std::string b = "abcdefg";
        std::string a;
        {
            boost::progress_timer t;
            for (int i = 0; i < count; ++i) {
                a.resize(0);
                oven::for_each(b, ::push_backer(a));
            }
        }
        BOOST_CHECK( equals(a, b) );
    }
}
