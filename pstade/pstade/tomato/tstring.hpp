#ifndef PSTADE_TOMATO_TSTRING_HPP
#define PSTADE_TOMATO_TSTRING_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <sstream> // basic_stringstream
#include <string>  // basic_string
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/oven/copy_range.hpp>
#include "./to_multibyte_to.hpp"


namespace pstade { namespace tomato {


typedef std::basic_string<TCHAR>
tstring;


typedef std::basic_stringstream<TCHAR>
tstringstream;


template< class Sequence > inline
Sequence const
tstring_to(tstring const& from)
{
    BOOST_MPL_ASSERT_NOT((boost::is_same<Sequence, tstring>));

#if defined(_UNICODE)
    return from|oven::copied;
#else
    return tomato::multibyte_to<Sequence>(from);
#endif
}


template< class Range > inline
tstring const
to_tstring(Range const& from)
{
    BOOST_MPL_ASSERT_NOT((boost::is_same<Range, tstring>));

#if defined(_UNICODE)
    return from|oven::copied;
#else
    return tomato::to_multibyte<tstring>(from);
#endif
}


} } // namespace pstade::tomato


#define PSTADE_TOMATO_TSTRINGIZE(Text) PSTADE_TOMATO_TSTRINGIZE_I(Text)

    #define PSTADE_TOMATO_TSTRINGIZE_I(Text) PSTADE_TOMATO_TSTRINGIZE_II(#Text)
    #define PSTADE_TOMATO_TSTRINGIZE_II(Str) _T(Str)


#endif
