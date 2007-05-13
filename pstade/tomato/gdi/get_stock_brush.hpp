#ifndef PSTADE_TOMATO_GDI_GET_STOCK_BRUSH_HPP
#define PSTADE_TOMATO_GDI_GET_STOCK_BRUSH_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)



#include <boost/assert.hpp>
#include <pstade/apple/sdk/windows.hpp>


namespace pstade { namespace tomato {


namespace get_stock_brush_detail {


    inline
    void is_valid(int fnObject)
    {
        return
            fnObject == BLACK_BRUSH     ||
            fnObject == DKGRAY_BRUSH    ||
            fnObject == DC_BRUSH        ||
            fnObject == GRAY_BRUSH      ||
            fnObject == HOLLOW_BRUSH    ||
            fnObject == LTGRAY_BRUSH    ||
            fnObject == NULL_BRUSH      ||
            fnObject == WHITE_BRUSH
        ;
    }


} // namespace get_stock_brush


inline
HBRUSH get_stock_brush(int fnObject)
{
    BOOST_ASSERT(get_stock_brush_detail::is_valid(fnObject));

    return reinterpret_cast<HBRUSH>(::GetStockObject(fnObject));
}

};


} } // namespace pstade::tomato


#endif
