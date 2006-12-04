#ifndef PSTADE_TOMATO_WIDECHAR_TO_MULTIBYTE_HPP
#define PSTADE_TOMATO_WIDECHAR_TO_MULTIBYTE_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <boost/utility/result_of.hpp>
#include <pstade/apple/atl/config.hpp> // ATL_VER
#include <pstade/apple/atl/conv.hpp>
#include <pstade/auto_castable.hpp>
#include <pstade/oven/c_str_range.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/pipable.hpp>


namespace pstade { namespace tomato {


template< class MultiByteSeq, class WideCharRange >
MultiByteSeq const
widechar_to(WideCharRange const& from)
{
    std::wstring tmp = from|oven::copied;

#if !(PSTADE_APPLE_ATL_VER < 0x0700)

    return ATL::CW2A(tmp.c_str()).operator LPSTR()
        | oven::as_c_str
        | oven::copied;

#else

    USES_CONVERSION_EX;
    return W2A_EX(tmp.c_str(), 128)
        | oven::as_c_str
        | oven::copied;

#endif
}


struct widechar_to_fun
{
    template< class MultiByteSeq, class WideCharRange >
    MultiByteSeq operator()(WideCharRange const& from, boost::type<MultiByteSeq>) const
    {
        return tomato::widechar_to<MultiByteSeq>(from);
    }
};

PSTADE_PIPABLE(to_multibyte, boost::result_of<auto_castable_fun(widechar_to_fun)>::type)


} } // namespace pstade::tomato


#endif
