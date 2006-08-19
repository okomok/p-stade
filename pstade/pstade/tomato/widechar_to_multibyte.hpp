#ifndef PSTADE_TOMATO_WIDECHAR_TO_MULTIBYTE_HPP
#define PSTADE_TOMATO_WIDECHAR_TO_MULTIBYTE_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <pstade/apple/atl/config.hpp> // ATL_VER
#include <pstade/apple/atl/conv.hpp>
#include <pstade/egg/baby_auto.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/null_terminate_range.hpp>


namespace pstade { namespace tomato {


template< class MultiByteSeq, class WideCharRange >
MultiByteSeq const
widechar_to(WideCharRange const& from)
{
    std::wstring tmp = from|oven::copied;

#if !(PSTADE_APPLE_ATL_VER < 0x0700)

    return ATL::CW2A(tmp.c_str()).operator LPSTR()
        | oven::null_terminated
        | oven::copied;

#else

    USES_CONVERSION_EX;
    return W2A_EX(tmp.c_str(), 128)
        | oven::null_terminated
        | oven::copied;

#endif
}


struct widechar_to_class
{
    template< class MultiByteSeq, class WideCharRange >
    static MultiByteSeq call(WideCharRange const& from)
    {
        return tomato::widechar_to<MultiByteSeq>(from);
    }
};


PSTADE_EGG_PIPABLE(to_multibyte, egg::baby_auto<widechar_to_class>)


} } // namespace pstade::tomato


#endif
