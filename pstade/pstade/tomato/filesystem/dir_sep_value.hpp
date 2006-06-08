#ifndef PSTADE_TOMATO_FILESYSTEM_DIR_SEP_VALUE_HPP
#define PSTADE_TOMATO_FILESYSTEM_DIR_SEP_VALUE_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/integral_c.hpp>
#include <pstade/apple/sdk/tchar.hpp>


namespace pstade { namespace tomato {


struct dir_sep :
    boost::mpl::integral_c<char, '\\'>
{ };


struct dir_wsep :
    boost::mpl::integral_c<wchar_t, L'\\'>
{ };


struct dir_tsep :
    boost::mpl::integral_c<TCHAR, _T('\\')>
{ };


} } // namespace pstade::tomato


#endif
