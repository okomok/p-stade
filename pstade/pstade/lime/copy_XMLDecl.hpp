#ifndef PSTADE_LIME_COPY_XMLDECL_HPP
#define PSTADE_LIME_COPY_XMLDECL_HPP


// PStade.Lime
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/algorithm.hpp> // copy
#include <pstade/oven/null_terminate_range.hpp>


namespace pstade { namespace lime {


template< class OutIter > inline
void copy_XMLDecl(OutIter out)
{
    oven::copy(
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"|oven::null_terminated,
        out
    );
}


} } // namespace pstade::lime


#endif
