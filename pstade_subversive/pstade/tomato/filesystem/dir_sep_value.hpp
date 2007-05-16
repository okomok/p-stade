#ifndef PSTADE_TOMATO_FILESYSTEM_DIR_SEP_VALUE_HPP
#define PSTADE_TOMATO_FILESYSTEM_DIR_SEP_VALUE_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/static_c.hpp>


namespace pstade { namespace tomato {


struct dir_sep :
    static_c<char, '\\'>
{ };


struct dir_wsep :
    static_c<wchar_t, L'\\'>
{ };


struct dir_tsep :
    static_c<TCHAR, _T('\\')>
{ };


} } // namespace pstade::tomato


#endif
