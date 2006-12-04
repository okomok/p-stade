#ifndef PSTADE_TOMATO_GDI_IS_DC_HPP
#define PSTADE_TOMATO_GDI_IS_DC_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp>
#include <pstade/for_debug.hpp>
#include <pstade/singleton.hpp>
#include "../boolean_cast.hpp"


namespace pstade { namespace tomato {


struct is_dc_fun
{
    typedef bool result_type;

    bool operator()(HDC hDC) const
    {
        pstade::for_debug();

        POINT pt = { 0 };
        return ::DPtoLP(hDC, &pt, 1)|booleanized;
    }
};


PSTADE_SINGLETON_CONST(is_dc_fun, is_dc)


} } // namespace pstade::tomato


#endif
