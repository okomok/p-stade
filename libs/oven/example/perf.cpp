
#define _SECURE_SCL 0
#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#define PSTADE_CONCEPT_CHECK
#include <pstade/oven/jointed.hpp>
#include <pstade/oven/copied.hpp>
#include <pstade/oven/distance.hpp>
#include <pstade/oven/memoized.hpp>
#include <pstade/oven/algorithm.hpp>
#include <iterator>
#include <string>
#include <boost/progress.hpp>
#include <iostream>
#include <pstade/used.hpp>
#include <vector>


using namespace pstade::oven;


int main()
{
    std::vector<std::string> v;

    {
        std::string s;
        for (int i = 0; i < 10000; ++i)
            s += "1234567890";
        v.push_back(s);
    }

    {
        std::string s;
        for (int i = 0; i < 10000; ++i)
            s += "abcdefghijh";
        v.push_back(s);
    }

    {
        std::string s;
        for (int i = 0; i < 10000; ++i)
            s += "@[:]!#%&#'($";
        v.push_back(s);
    }

    {
        boost::progress_timer t;
        for (int i = 0; i < 3000; ++i) {
            char l = (v[0] + v[1] + v[2] + v[0] + v[1] + v[2])[i];
            pstade::used(l);
        }
    }
    {
        boost::progress_timer t;
        for (int i = 0; i < 3000; ++i) {
            char l = (v[0]|jointed(v[1])|jointed(v[2])|jointed(v[0])|jointed(v[1])|jointed(v[2]))[i];
            pstade::used(l);
        }
    }
}
