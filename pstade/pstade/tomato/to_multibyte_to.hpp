#ifndef PSTADE_TOMATO_TO_MULTIBYTE_TO_HPP
#define PSTADE_TOMATO_TO_MULTIBYTE_TO_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <pstade/apple/atl/config.hpp> // ATL_VER
#include <pstade/apple/atl/conv.hpp>
#include <pstade/oven/null_terminate_range.hpp>
#include <pstade/oven/sequence_cast.hpp>


namespace pstade { namespace tomato {


template< class DstSeq, class SrcRng >
DstSeq to_multibyte(const SrcRng& src)
{
    std::wstring tmp = oven::sequence(src);

#if !(PSTADE_APPLE_ATL_VER < 0x0700)
    return oven::sequence(
        ATL::CW2A(tmp.c_str()).operator LPSTR() |
            oven::null_terminated
    );
#else
    USES_CONVERSION_EX;
    return oven::sequence(
        W2A_EX(tmp.c_str(), 128) |
           oven::null_terminated
    );
#endif
}


template< class DstSeq, class SrcRng >
DstSeq multibyte_to(const SrcRng& src)
{
    std::string tmp = oven::sequence(src);

#if !(PSTADE_APPLE_ATL_VER < 0x0700)
    return oven::sequence(
        ATL::CA2W(tmp.c_str()).operator LPWSTR() |
            oven::null_terminated
    );
#else
    USES_CONVERSION_EX;
    return oven::sequence(
        A2W_EX(tmp.c_str(), 128) |
            oven::null_terminated
    );
#endif
}


} } // namespace pstade::tomato


#endif
