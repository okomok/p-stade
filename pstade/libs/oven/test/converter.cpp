#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/converter.hpp>
#include <pstade/minimal_test.hpp>


#include <algorithm>
#include <iterator>
#include <vector>
#include <pstade/oven/equals.hpp>



struct my_length
{
    my_length(std::string const s)
    {
        len = s.size();
    }

    int len;
};


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;


    std::vector<std::string> vs;
    vs.push_back("1234567");
    vs.push_back("12345");
    vs.push_back("123456789");


    {
        std::vector<my_length> vo;

        std::copy(boost::begin(vs), boost::end(vs),
            converter<my_length>() |= std::back_inserter(vo));

        BOOST_CHECK( vo[0].len == 7 );
        BOOST_CHECK( vo[1].len == 5 );
        BOOST_CHECK( vo[2].len == 9 );
    }

    {
        std::vector<my_length> vo;

        std::copy(boost::begin(vs), boost::end(vs),
            oven::make_converter<my_length>(std::back_inserter(vo)));

        BOOST_CHECK( vo[0].len == 7 );
        BOOST_CHECK( vo[1].len == 5 );
        BOOST_CHECK( vo[2].len == 9 );
    }
}
