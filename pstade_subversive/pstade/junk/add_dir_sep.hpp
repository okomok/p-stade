#ifndef PSTADE_TOMATO_FILESYSTEM_ADD_DIR_SEP_HPP
#define PSTADE_TOMATO_FILESYSTEM_ADD_DIR_SEP_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./dir_sep_value.hpp"


namespace pstade { namespace tomato {


template< class StringT >
void add_dir_sep(StringT& str)
{
    if (
        str.IsEmpty() ||
        (str[str.GetLength() - 1] != tdir_sep::value)
    )
    {
        str += tdir_sep::value;
    }
}


} } // namespace pstade::tomato


#endif
