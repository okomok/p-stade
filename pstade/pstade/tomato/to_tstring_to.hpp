#ifndef PSTADE_TOMATO_TO_TSTRING_TOHPP
#define PSTADE_TOMATO_TO_TSTRING_TOHPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/ambi.hpp>
#include <pstade/egg/by_cref.hpp>
#include <pstade/gravy/sdk/tchar.hpp>
#include <pstade/gravy/tstring.hpp>
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


    namespace to_tstring_detail {


        struct little
        {
            template<class Myself, class WideCharSeq>
            struct apply
            {
                typedef gravy::tstring const type;
            };

            template<class Result, class WideCharSeq>
            Result call(WideCharSeq& from) const
            {
#if defined(_UNICODE)
                return from|oven::copied;
#else
                return tomato::widechar_to<gravy::tstring>(from);
#endif
            }
        };


        typedef egg::function<little, egg::by_cref> op;


    } // namespace to_string_detail


    PSTADE_POD_CONSTANT((egg::result_of_ambi0<to_tstring_detail::op>::type), to_tstring)
        = PSTADE_EGG_AMBI({{}});


} } // namespace pstade::tomato


#endif
