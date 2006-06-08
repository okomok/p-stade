#ifndef PSTADE_LIME_DETAIL_INCLUDE_FILE_HPP
#define PSTADE_LIME_DETAIL_INCLUDE_FILE_HPP


// PStade.Lime
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <pstade/oven/equal.hpp>
#include <pstade/oven/sequence_cast.hpp>
#include <pstade/ustring.hpp>
#include "./load_file_fwd.hpp"
#include "./node_fwd.hpp"


namespace pstade { namespace lime { namespace detail {


template< class Interface >
void include_file(node<Interface>& n)
{
    if (oven::equals(n.name(), pstade::ustring("include"))) {
        std::string path = oven::sequence_cast<std::string>(n.att("href"));
        lime::load_file(n, path);
    }
}


} } } // namespace pstade::lime::detail


#endif
