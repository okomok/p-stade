#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// ASCII file only.
// newline character must be '\n'.
// tabsize is 4.


#include <pstade/oven.hpp>


#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <boost/cstdint.hpp>
#include <boost/foreach.hpp>
#include <pstade/garlic.hpp>
#include <pstade/wine.hpp>


using namespace pstade;


void unexpand_tab(std::string fileName)
{
    std::vector<boost::uint8_t> buf; {
        oven::copy(
            oven::file_range<boost::uint8_t>(fileName) |
                pstade::required("non-empty input file: " + fileName) |
                oven::tab_unexpanded(4),
            garlic::back_inserter(buf)
        );
    }

    std::ofstream fout(fileName.c_str(), std::ios::binary);
    pstade::require(fout, "good output file: " + fileName);
    oven::copy(buf, garlic::back_inserter(fout));
};


int main(int argc, char *argv[])
{
    BOOST_FOREACH (int i, oven::one_to(argc)) {

        try {
            ::unexpand_tab(argv[i]);
        }
        catch (std::exception& err) {
            std::cout << err.what() << std::endl;
        }

    }

    return std::cout << "<press-any-key/>", pstade::pause();
}
