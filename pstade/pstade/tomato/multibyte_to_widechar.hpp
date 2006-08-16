#ifndef PSTADE_TOMATO_MULTIBYTE_TO_WIDECHAR_HPP
#define PSTADE_TOMATO_MULTIBYTE_TO_WIDECHAR_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <pstade/apple/atl/config.hpp> // ATL_VER
#include <pstade/apple/atl/conv.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/nonassignable.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/null_terminate_range.hpp>


namespace pstade { namespace tomato {


template< class WideCharSeq, class  MultiByteRange >
WideCharSeq multibyte_to(MultiByteRange const& from)
{
    std::string tmp = from|oven::copied;

#if !(PSTADE_APPLE_ATL_VER < 0x0700)

    return ATL::CA2W(tmp.c_str()).operator LPWSTR()
        | oven::null_terminated
        | oven::copied;

#else

    USES_CONVERSION_EX;
    return A2W_EX(tmp.c_str(), 128)
        | oven::null_terminated
        | oven::copied;

#endif
}


namespace to_widechar_detail {


    template< class MultiByteRange >
    struct temp :
        private nonassignable
    {
        explicit temp(MultiByteRange& from) :
            m_from(from)
        { }

        template< class WideCharSeq >
        operator WideCharSeq() const
        {
            return tomato::multibyte_to<WideCharSeq>(m_from);
        }

    private:
        MultiByteRange& m_from;
    };


    struct baby
    {
        template< class Unused, class MultiByteRange >
        struct result
        {
            typedef temp<MultiByteRange> const type;
        };

        template< class Result, class MultiByteRange >
        Result call(MultiByteRange& from)
        {
            return Result(from);
        }
    };


} // namespace to_widechar_detail


PSTADE_EGG_PIPABLE(to_widechar, to_widechar_detail::baby)


} } // namespace pstade::tomato


#endif
