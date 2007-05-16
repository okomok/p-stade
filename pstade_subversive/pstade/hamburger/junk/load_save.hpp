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
#include <pstade/lime/load.hpp>
#include <pstade/oven/copy.hpp>
#include <pstade/oven/sequence_cast.hpp>
#include <pstade/oven/utf8_decode_range.hpp>
#include <pstade/tomato/file_range.hpp>
#include <pstade/tomato/to_multibyte_to.hpp>
#include <pstade/tomato/tstring.hpp>
#include <pstade/ustring.hpp>


namespace pstade { namespace hamburger {


template< class Node >
void load(Node& root, ustring path)
{
    // cache for speed
    ustring tmp; {

#if defined(_UNICODE)
        tomato::tstring path_ = oven::sequence(path);
#else
        tomato::tstring path_ = tomato::to_multibyte<tomato::tstring>(path);
#endif

        tomato::ifile_range<> frng(path_);
        oven::copy(
            frng |
                oven::utf8_decoded,
            garlic::back_inserter(tmp)
        );

    }

    lime::load(root, tmp);
}


template< class Node >
void save(Node& root, ustring path)
{
    std::vector<utf8cp_t> tmp;
    lime::copy_XMLDecl(garlic::back_inserter(tmp));
    lime::save_default(node, oven::utf8_encoder(garlic::back_inserter(tmp)));

#if defined(_UNICODE)
    tomato::tstring path = oven::sequence(node%Name_includedHref);
#else
    tomato::tstring path = tomato::to_multibyte<tomato::tstring>(node%Name_includedHref);
#endif

    oven::copies(tmp, tomato::ofile_range<utf8cp_t>(path, tmp.size());
}


} } // namespace pstade::hamburger


#endif
