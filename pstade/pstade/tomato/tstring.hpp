#ifndef PSTADE_TOMATO_TSTRING_HPP
#define PSTADE_TOMATO_TSTRING_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <sstream> // basic_stringstream
#include <string>  // basic_string
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pipable.hpp>
#include <pstade/oven/copy_range.hpp>
#include "./multibyte_to_widechar.hpp"
#include "./widechar_to_multibyte.hpp"


namespace pstade { namespace tomato {


typedef std::basic_string<TCHAR>
tstring;


typedef std::basic_stringstream<TCHAR>
tstringstream;


template< class WideCharSeq > inline
WideCharSeq const
tstring_to(tstring const& from)
{
#if defined(_UNICODE)
    return from|oven::copied;
#else
    return tomato::multibyte_to<WideCharSeq>(from);
#endif
}


namespace to_tstring_detail {


    struct baby
    {
        template< class Myself, class WideCharSeq >
        struct apply
        {
            typedef tstring const type;
        };

        template< class Result, class WideCharSeq >
        Result call(WideCharSeq const& from) const
        {
        #if defined(_UNICODE)
            return from|oven::copied;
        #else
            return tomato::widechar_to<tstring>(from);
        #endif
        }
    };


} // namespace to_tstring_detail


PSTADE_PIPABLE(to_tstring, egg::function<to_tstring_detail::baby>)


} } // namespace pstade::tomato


#define PSTADE_TOMATO_TSTRINGIZE(Text) PSTADE_TOMATO_TSTRINGIZE_I(Text)

    #define PSTADE_TOMATO_TSTRINGIZE_I(Text) PSTADE_TOMATO_TSTRINGIZE_II(#Text)
    #define PSTADE_TOMATO_TSTRINGIZE_II(Str) _T(Str)


#endif
