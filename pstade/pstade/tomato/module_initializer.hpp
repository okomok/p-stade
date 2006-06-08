#ifndef PSTADE_TOMATO_MODULE_INITIALIZER_HPP
#define PSTADE_TOMATO_MODULE_INITIALIZER_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/atl/module.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/require.hpp>
#include "./succeeded.hpp"


namespace pstade { namespace tomato {


namespace module_initializer_detail {


    inline
    void resolve_thunking_problem()
    {
        // Workaround:
        // This resolves ATL window thunking problem
        // when Microsoft Layer for Unicode (MSLU) is used.
        ::DefWindowProc(NULL, 0, 0, 0L);    
    }


} // namespace module_initializer_detail


struct module_initializer
{
    explicit module_initializer(HINSTANCE hInstance)
    {
        PSTADE_REQUIRE(tomato::succeeded(_Module.Init(NULL, hInstance)));
        module_initializer_detail::resolve_thunking_problem();
    }

    ~module_initializer()
    {
        _Module.Term();
    }
};


} } // namespace pstade::tomato


#endif
