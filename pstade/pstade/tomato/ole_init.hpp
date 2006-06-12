#ifndef PSTADE_TOMATO_OLE_INIT_HPP
#define PSTADE_TOMATO_OLE_INIT_HPP


// PStade.Tomato
//
// Olepyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/ole2.hpp>
#include <pstade/require.hpp>
#include "./succeeded.hpp"


namespace pstade { namespace tomato {


struct ole_init
{
    ole_init()
    {
        PSTADE_REQUIRE(tomato::succeeded(::OleInitialize(NULL)));
    }

    ~ole_init()
    {
        ::OleUninitialize();
    }
};


} } // namespace pstade::tomato



#endif
