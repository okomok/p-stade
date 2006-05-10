#ifndef PSTADE_LIME_SAVE_FILE_HPP
#define PSTADE_LIME_SAVE_FILE_HPP


// PStade.Lime
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <fstream>
#include <string>
#include <pstade/garlic/back_inserter.hpp>
#include <pstade/oven/copy.hpp>
#include <pstade/oven/null_terminate_range.hpp>
#include <pstade/oven/utf8_encoder.hpp>
#include <pstade/require.hpp>
#include "./detail/node_fwd.hpp"
#include "./save.hpp"


namespace pstade { namespace lime {


template< class Interface >
void save_file(node<Interface>& root, std::string fileName)
{
    std::ofstream fout(fileName.c_str(), std::ios::binary);
    pstade::require(fout, "good output file: " + fileName);

    oven::copy(
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"|oven::null_terminated,
        oven::utf8_encoder(garlic::back_inserter(fout))
    );

    return lime::save(root, oven::utf8_encoder(garlic::back_inserter(fout)));
}


} } // namespace pstade::lime


#endif
