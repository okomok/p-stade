#ifndef PSTADE_GRAVY_DETAIL_IS_BRUSH_HPP
#define PSTADE_GRAVY_DETAIL_IS_BRUSH_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/for_debug.hpp>
#include <pstade/pod_constant.hpp>
#include "../boolean_cast.hpp"
#include "../sdk/windows.hpp"


namespace pstade { namespace gravy { namespace detail {


    struct op_is_brush
    {
        typedef bool result_type;

        bool operator()(HBRUSH h) const
        {
            for_debug();

            return h != NULL; // how?
        }
    };


    PSTADE_POD_CONSTANT((op_is_brush), is_brush) = {};


} } } // namespace pstade::gravy::detail


#endif
