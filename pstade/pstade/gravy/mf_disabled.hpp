#ifndef PSTADE_GRAVY_MF_DISABLED_HPP
#define PSTADE_GRAVY_MF_DISABLED_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/static_c.hpp>
#include "./sdk/windows.hpp"


namespace pstade { namespace gravy {


    struct mf_disabled :
#if !defined(_WIN32_WCE)
        static_c<UINT, MF_DISABLED>
#else
        static_c<UINT, 0>
#endif
    { };


} } // namespace pstade::gravy


#endif
