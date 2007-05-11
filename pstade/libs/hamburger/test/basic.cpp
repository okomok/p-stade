#define _WIN32_WINNT 0x0500
#include <pstade/unit_test.hpp>


#include <pstade/apple/wtl/app.hpp>
WTL::CAppModule _Module;


// PStade.Lime
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/hamburger.hpp>


#include <iterator>
#include <fstream>
#include <iterator>
#include <iostream>
#include <string>
#include <pstade/oven.hpp>
#include <pstade/wine.hpp>
#include <pstade/lime.hpp>


void pstade_unit_test()
{
	using namespace pstade;

    std::cout << "<hamburger_test>";

	try {

		std::string iname("sample_view.xml");
		std::cout << "<input-file>" << iname << "</input-file>";

		std::string oname = iname + ".out";
		std::ofstream fout(oname.c_str(), std::ios::binary);
		pstade::require(fout, "good output file: " + oname);

		ustring tmp; {// for speed
			oven::copy(
				oven::file_range<utf8cp_t>(iname) |
					oven::utf8_decoded,
				std::back_inserter(tmp)
			);
		}

        hamburger::element root;
        lime::load(root, tmp);

		lime::save(
			root.front(),
			oven::utf8_encoder(oven::stream_writer(fout))
		);

	}
	catch (std::exception& err) {
        std::cout << "<error>" << err.what() << "</error>\n";
	}

    std::cout << "</hamburger_test>";
}

