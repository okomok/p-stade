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
#include <pstade/automatic.hpp>
#include <pstade/auxiliary.hpp>
#include <pstade/oven/as_c_str.hpp>
#include <pstade/oven/copy_range.hpp>

namespace pstade { namespace tomato {


template<class WideCharSeq, class MultiByteRange>
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


template<class To>
struct op_multibyte_to
{
    typedef To result_type;

    template<class From>
    To operator()(From const& from) const
    {
        return tomato::multibyte_to<To>(from);
    }
};

PSTADE_AUXILIARY(0, to_widechar, (automatic<op_multibyte_to<boost::mpl::_1> >))


} } // namespace pstade::tomato


#endif
