#ifndef PSTADE_NAPKIN_DOUT_HPP
#define PSTADE_NAPKIN_DOUT_HPP


// PStade.Napkin
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp>
#include <pstade/instance.hpp>


namespace pstade { namespace napkin {


namespace dout_detail {


    struct out
    {
        void operator<<(const char *psz) const
        {
            ::OutputDebugStringA(psz);
        }

        void operator<<(const wchar_t *psz) const
        {
            ::OutputDebugStringW(psz);
        }
    };


} // namespace dout_detail


PSTADE_INSTANCE(const dout_detail::out, dout, value)


} } // namespace pstade::napkin


#endif
