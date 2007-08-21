#ifndef PSTADE_TOMATO_MULTIBYTE_TO_WIDECHAR_HPP
#define PSTADE_TOMATO_MULTIBYTE_TO_WIDECHAR_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <pstade/egg/automatic.hpp>
#include <pstade/egg/auxiliary.hpp>
#include <pstade/oven/as_c_str.hpp>
#include <pstade/oven/copied.hpp>
#include <pstade/pod_constant.hpp>
#include "./atl/config.hpp" // ATL_VER
#include "./atl/conv.hpp"


namespace pstade { namespace tomato {


    template<class WideCharSeq, class MultiByteRange>
    WideCharSeq const
    multibyte_to(MultiByteRange const& from)
    {
        std::string tmp = from|oven::copied;

#if !(PSTADE_TOMATO_ATL_VER < 0x0700)

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
    struct xp_multibyte_to
    {
        typedef To result_type;

        template<class From>
        To operator()(From const& from) const
        {
            return tomato::multibyte_to<To>(from);
        }
    };


    typedef
        egg::result_of_auxiliary0<
            egg::automatic< xp_multibyte_to<boost::mpl::_> >::type
        >::type
    op_to_widechar;


    PSTADE_POD_CONSTANT((op_to_widechar), to_widechar)
        = PSTADE_EGG_AUXILIARY_L PSTADE_EGG_AUTOMATIC PSTADE_EGG_AUXILIARY_R;


} } // namespace pstade::tomato


#endif
