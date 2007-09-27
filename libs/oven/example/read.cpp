#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#define PSTADE_CONCEPT_CHECK
#include <fstream>
#include <string>
#include <vector>
#include <pstade/oven/algorithm.hpp>
#include <pstade/oven/stream_read.hpp>
#include <pstade/oven/stream_writer.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/initial_values.hpp>
#include <pstade/oven/io.hpp>


#include <pstade/oven/alias.hpp>
using namespace oven;


int test_main(int, char*[])
{
    std::vector<std::string> sample
        = initial_values("hello", "oven", "stream_read");

    {
        std::ofstream fout("read.txt");
        copy(sample, stream_writer(" ")|=fout);
    }

    {
        std::ifstream fin("read.txt");
        BOOST_CHECK( equals(
            oven::stream_read<std::string>(fin),
            sample
        ) );
    }

    return 0;
}
