#pragma once

#include <boost/mpl/integral_c.hpp>

namespace pstade { namespace tomato {


struct dir_separator :
	boost::mpl::integral_c<char, '\\'>
{ };

struct wdir_separator :
	boost::mpl::integral_c<wchar_t, L'\\'>
{ };

struct tdir_separator :
	boost::mpl::integral_c<TCHAR, _T('\\')>
{ };


} } // namespace pstade::tomato
