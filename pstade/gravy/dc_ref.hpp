#ifndef PSTADE_GRAVY_DC_REF_HPP
#define PSTADE_GRAVY_DC_REF_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/handle_ref.hpp"
#include "./detail/is_dc.hpp"
#include "./sdk/windows.hpp"


namespace pstade { namespace gravy {


    typedef
        detail::handle_ref<HDC, detail::op_is_dc>
    dc_ref;


} } // namespace pstade::gravy


#endif
