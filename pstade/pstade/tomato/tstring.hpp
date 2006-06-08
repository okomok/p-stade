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
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/oven/sequence_cast.hpp>
#include <pstade/ustring.hpp>
#include "./to_multibyte_to.hpp"


namespace pstade { namespace tomato {


typedef std::basic_string<TCHAR>
tstring;


typedef std::basic_stringstream<TCHAR>
tstringstream;


template< class DstSeq > inline
DstSeq tstring_to(tstring str)
{
    BOOST_STATIC_ASSERT(( !boost::is_same<DstSeq, tstring>::value ));

#if defined(_UNICODE)
    return oven::sequence(str);
#else
    return tomato::multibyte_to<DstSeq>(str);
#endif
}


template< class SrcRng > inline
tstring to_tstring(const SrcRng& str)
{
    BOOST_STATIC_ASSERT(( !boost::is_same<SrcRng, tstring>::value ));

#if defined(_UNICODE)
    return oven::sequence(str);
#else
    return tomato::to_multibyte<tstring>(str);
#endif
}


} } // namespace pstade::tomato


#define PSTADE_TOMATO_TSTRINGIZE(Text) PSTADE_TOMATO_TSTRINGIZE_I(Text)

    #define PSTADE_TOMATO_TSTRINGIZE_I(Text) PSTADE_TOMATO_TSTRINGIZE_II(#Text)
    #define PSTADE_TOMATO_TSTRINGIZE_II(Str) _T(Str)


#endif
