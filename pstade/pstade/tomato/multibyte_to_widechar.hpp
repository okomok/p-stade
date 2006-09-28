#ifndef PSTADE_TOMATO_MULTIBYTE_TO_WIDECHAR_HPP
#define PSTADE_TOMATO_MULTIBYTE_TO_WIDECHAR_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <pstade/apple/atl/config.hpp> // ATL_VER
#include <pstade/apple/atl/conv.hpp>
#include <pstade/egg/baby_auto.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/oven/c_str_range.hpp>
#include <pstade/oven/copy_range.hpp>


namespace pstade { namespace tomato {


template< class WideCharSeq, class MultiByteRange >
WideCharSeq const
multibyte_to(MultiByteRange const& from)
{
    std::string tmp = from|oven::copied;

#if !(PSTADE_APPLE_ATL_VER < 0x0700)

    return ATL::CA2W(tmp.c_str()).operator LPWSTR()
        | oven::as_c_str
        | oven::copied;

#else

    USES_CONVERSION_EX;
    return A2W_EX(tmp.c_str(), 128)
        | oven::as_c_str
        | oven::copied;

#endif
}


struct multibyte_to_class
{
    template< class WideCharSeq, class MultiByteRange >
    static WideCharSeq call(MultiByteRange const& from)
    {
        return tomato::multibyte_to<WideCharSeq>(from);
    }
};


PSTADE_EGG_PIPABLE(to_widechar, egg::baby_auto<multibyte_to_class>)


} } // namespace pstade::tomato


#endif
