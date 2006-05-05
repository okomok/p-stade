#ifndef PSTADE_TOMATO_CO_INITIALIZER_HPP
#define PSTADE_TOMATO_CO_INITIALIZER_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/sdk/windows.hpp>
#include <pstade/require.hpp>


namespace pstade { namespace tomato {


struct co_initializer
{
    explicit co_initializer()
    {
        HRESULT hr = ::CoInitialize(NULL);
        pstade::require(SUCCEEDED(hr), "::Coninitialize");
    }

    ~co_initializer()
    {
        ::CoUninitialize();
    }
};


} } // namespace pstade::tomato



#endif
