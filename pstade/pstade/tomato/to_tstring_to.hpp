#ifndef PSTADE_TOMATO_TO_TSTRING_TOHPP
#define PSTADE_TOMATO_TO_TSTRING_TOHPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/callable.hpp>
#include <pstade/gravy/sdk/tchar.hpp>
#include <pstade/gravy/tstring.hpp>
#include <pstade/pipable.hpp>
#include <pstade/oven/copied.hpp>
#include "./multibyte_to_widechar.hpp"
#include "./widechar_to_multibyte.hpp"


namespace pstade { namespace tomato {


    template<class WideCharSeq> inline
    WideCharSeq const
    tstring_to(gravy::tstring const& from)
    {
 #if defined(_UNICODE)
        return from|oven::copied;
#else
        return tomato::multibyte_to<WideCharSeq>(from);
#endif
    }


    struct op_to_tstring :
        callable<op_to_tstring>
    {
        template<class Myself, class WideCharSeq>
        struct apply
        {
            typedef gravy::tstring const type;
        };

        template<class Result, class WideCharSeq>
        Result call(WideCharSeq const& from) const
        {
#if defined(_UNICODE)
            return from|oven::copied;
#else
            return tomato::widechar_to<gravy::tstring>(from);
#endif
        }
    };


    PSTADE_PIPABLE(to_tstring, (op_to_tstring))


} } // namespace pstade::tomato


#endif
