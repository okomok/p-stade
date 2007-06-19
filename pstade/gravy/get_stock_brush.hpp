#ifndef PSTADE_GRAVY_GET_STOCK_BRUSH_HPP
#define PSTADE_GRAVY_GET_STOCK_BRUSH_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/constant.hpp>
#include "./brush_ref.hpp"
#include "./handle_cast.hpp"
#include "./sdk/windows.hpp"


namespace pstade { namespace gravy {


    namespace get_stock_brush_detail {


        inline
        bool valid(int fnObject)
        {
            return
                fnObject == BLACK_BRUSH     ||
                fnObject == DKGRAY_BRUSH    ||
#if (_WIN32_WINNT >= 0x0500)
                fnObject == DC_BRUSH        ||
#endif
                fnObject == GRAY_BRUSH      ||
                fnObject == HOLLOW_BRUSH    ||
                fnObject == LTGRAY_BRUSH    ||
                fnObject == NULL_BRUSH      ||
                fnObject == WHITE_BRUSH
            ;
        }


    } // namespace get_stock_brush_detail


    struct op_get_stock_brush
    {
        typedef brush_ref result_type;

        brush_ref operator()(int fnObject) const
        {
            BOOST_ASSERT(get_stock_brush_detail::valid(fnObject));
            return gravy::handle_cast<HBRUSH>(::GetStockObject(fnObject));
        }
    };


    PSTADE_CONSTANT(get_stock_brush, (op_get_stock_brush))


} } // namespace pstade::gravy


#endif
