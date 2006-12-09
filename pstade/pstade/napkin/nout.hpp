#ifndef PSTADE_NAPKIN_NOUT_HPP
#define PSTADE_NAPKIN_NOUT_HPP


// PStade.Napkin
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/constant.hpp>
#include <pstade/unused.hpp>


namespace pstade { namespace napkin {


namespace nout_detail {


    struct out
    {
        void operator<<(const char *psz) const
        {
            pstade::unused(psz);
        }

        void operator<<(const wchar_t *psz) const
        {
            pstade::unused(psz);
        }
    };


} // namespace nout_detail


PSTADE_CONSTANT(nout, nout_detail::out)


} } // namespace pstade::napkin


#endif
