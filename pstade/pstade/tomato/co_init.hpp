#ifndef PSTADE_TOMATO_CO_INIT_HPP
#define PSTADE_TOMATO_CO_INIT_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/objbase.hpp>
#include <pstade/require.hpp>
#include "./succeeded.hpp"


namespace pstade { namespace tomato {


struct co_init
{
    explicit co_init()
    {
        PSTADE_REQUIRE(tomato::succeeded(::CoInitialize(NULL)));
    }

#if (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) // DCOM
    explicit co_init(DWORD dwCoInit)
    {
        PSTADE_REQUIRE(tomato::succeeded(::CoInitializeEx(NULL, dwCoInit)));
    }
#endif

    ~co_init()
    {
        ::CoUninitialize();
    }
};


} } // namespace pstade::tomato



#endif
