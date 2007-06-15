#ifndef PSTADE_GRAVY_CO_INIT_HPP
#define PSTADE_GRAVY_CO_INIT_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/require.hpp>
#include "./include/objbase.hpp"
#include "./include/winerror.hpp"


namespace pstade { namespace gravy {


    struct co_init
    {
        explicit co_init()
        {
            PSTADE_REQUIRE( SUCCEEDED(::CoInitialize(NULL)) );
        }

    #if (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) // DCOM
        explicit co_init(DWORD dwCoInit)
        {
            PSTADE_REQUIRE( SUCCEEDED(::CoInitializeEx(NULL, dwCoInit)) );
        }
    #endif

        ~co_init()
        {
            ::CoUninitialize();
        }
    };


} } // namespace pstade::gravy



#endif
