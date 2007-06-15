#ifndef PSTADE_GRAVY_SET_WINDOW_TEXT_HPP
#define PSTADE_GRAVY_SET_WINDOW_TEXT_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of:
//
// MFC7::AfxSetWindowText


#include <boost/array.hpp>
#include <boost/range/begin.hpp>
#include <pstade/constant.hpp>
#include <pstade/copy_construct.hpp>
#include <pstade/oven/as_c_str.hpp>
#include <pstade/oven/distance.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/iter_range.hpp>
#include <pstade/require.hpp>
#include <pstade/static_c.hpp>
#include "./c_str.hpp"
#include "./sdk/tchar.hpp"
#include "./sdk/windows.hpp"
#include "./window_ref.hpp"


namespace pstade { namespace gravy {


    struct op_set_window_text
    {
        typedef void result_type;

        template< class CStringizable >
        void operator()(window_ref wnd, CStringizable const& str) const
        {
            TCHAR const *pszNew = c_str(str);
            oven::iter_range<TCHAR const *> rngNew(pszNew|oven::as_c_str);
            int newLen = pstade::copy_construct<int>(oven::distance(rngNew));

            typedef static_c<int, 255> bufLen;
            boost::array<TCHAR, 1 + bufLen::value> bufOld;

            // fast check to see if text really changes (reduces flash in controls)
            if (newLen > bufLen::value ||
                ::GetWindowText(wnd, boost::begin(bufOld), bufOld.static_size) != newLen ||
                !oven::equals(bufOld|oven::as_c_str, rngNew))
            {
                PSTADE_REQUIRE(::SetWindowText(wnd, pszNew));
            }
        }
    };


    PSTADE_CONSTANT(set_window_text, (op_set_window_text))


} } // namespace pstade::gravy


#endif
