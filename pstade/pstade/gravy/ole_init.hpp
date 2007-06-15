#ifndef PSTADE_GRAVY_OLE_INIT_HPP
#define PSTADE_GRAVY_OLE_INIT_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/require.hpp>
#include "./sdk/ole2.hpp"
#include "./sdk/winerror.hpp" // SUCCEEDED


namespace pstade { namespace gravy {


    struct ole_init
    {
        ole_init()
        {
            PSTADE_REQUIRE( SUCCEEDED(::OleInitialize(NULL)) );
        }

        ~ole_init()
        {
            ::OleUninitialize();
        }
    };


} } // namespace pstade::gravy



#endif
