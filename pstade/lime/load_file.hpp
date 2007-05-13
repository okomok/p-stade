#ifndef PSTADE_LIME_LOAD_FILE_HPP
#define PSTADE_LIME_LOAD_FILE_HPP


// PStade.Lime
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iterator> // back_inserter
#include <string>
#include <pstade/oven/algorithm.hpp> // copy
#include <pstade/oven/file_range.hpp>
#include <pstade/oven/utf8_decoded.hpp>
#include <pstade/ustring.hpp> // utf8cp_t
#include "./load.hpp"


namespace pstade { namespace lime {


    template< class Node >
    void load_file(Node& root, std::string const& fileName)
    {
        ustring tmp; { // cache for speed
            oven::file_range<utf8cp_t> frng(fileName);
            oven::copy(frng|oven::utf8_decoded, std::back_inserter(tmp));
        }

        lime::load(root, tmp);
    }


} } // namespace pstade::lime


#endif
