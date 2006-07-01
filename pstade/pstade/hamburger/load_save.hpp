#ifndef PSTADE_HAMBURGER_LOAD_SAVE_HPP
#define PSTADE_HAMBURGER_LOAD_SAVE_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <vector>
#include <pstade/garlic/back_inserter.hpp>
#include <pstade/lime/copy_XMLDecl.hpp>
#include <pstade/lime/load.hpp>
#include <pstade/lime/save.hpp>
#include <pstade/oven/algorithm.hpp> // copy
#include <pstade/oven/copies.hpp>
#include <pstade/oven/null_outputter.hpp>
#include <pstade/oven/sequence_cast.hpp>
#include <pstade/oven/utf8_decode_range.hpp>
#include <pstade/tomato/file_range.hpp>
#include <pstade/tomato/tstring.hpp>
#include <pstade/ustring.hpp>


namespace pstade { namespace hamburger {


template< class Node >
void load(Node& node, ustring path)
{
    // cache for speed
    std::vector<ucs4_t> tmp;
    tomato::ifile_range<utf8cp_t> irng(tomato::to_tstring(path));
    oven::copy(
        irng |
            oven::utf8_decoded,
        garlic::back_inserter(tmp)
    );

    lime::load(node, tmp);
}


template< class Node > inline
void save(Node& node)
{
    lime::save(node, oven::null_outputter);
}


template< class Node >
void save(Node& node, ustring path)
{
    std::vector<utf8cp_t> tmp;
    lime::copy_XMLDecl(garlic::back_inserter(tmp));
    lime::save_default(node, oven::utf8_encoder(garlic::back_inserter(tmp)));

    tomato::ofile_range<utf8cp_t> orng(tomato::to_tstring(path), tmp.size());
    oven::copies(tmp, orng);
}


} } // namespace pstade::hamburger


#endif
