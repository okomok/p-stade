#include <pstade/vodka/begin.hpp>


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)]


#include <fstream>
#include <string>


#include <pstade/biscuit.hpp>
#include <pstade/require.hpp>


#include "./cpp_to_xhtml.hpp"


int main(int argc, char* argv[])
{
    for (int i = 0; ++i < argc;) {
        std::string filename(argv[i]);
        std::ifstream ifs(filename.c_str());
        std::string text;
        std::getline(ifs, text, '\0');
        tab2space(text);

        std::ofstream ofs( (filename+".xhtml").c_str() );

        ofs << "<pre class=\"cpp_source\">\n";
        PSTADE_REQUIRE( biscuit::match< cpp_to_xhtml::start >(text, ofs) );
        ofs << "</pre>\n";
    }
    return 0;
}
