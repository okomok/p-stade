#ifndef PSTADE_GRAVY_DIR_SEP_HPP
#define PSTADE_GRAVY_DIR_SEP_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/static_c.hpp>
#include "./sdk/windows.hpp"


namespace pstade { namespace gravy {


    struct dir_sep :
        static_c<char, '\\'>
    { };


    struct dir_wsep :
        static_c<wchar_t, L'\\'>
    { };


    struct dir_tsep :
        static_c<TCHAR, _T('\\')>
    { };


} } // namespace pstade::gravy


#endif
