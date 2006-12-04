#ifndef PSTADE_NAPKIN_DOUT_HPP
#define PSTADE_NAPKIN_DOUT_HPP


// PStade.Napkin
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp>
#include <pstade/singleton.hpp>


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


PSTADE_SINGLETON_CONST(dout_detail::out, dout)


} } // namespace pstade::napkin


#endif
