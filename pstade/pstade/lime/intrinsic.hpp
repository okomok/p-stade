#ifndef PSTADE_LIME_INTRINSIC_HPP
#define PSTADE_LIME_INTRINSIC_HPP


// PStade.Lime
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/instance.hpp>
#include <pstade/ustring.hpp>


namespace pstade { namespace lime {


    PSTADE_INSTANCE(const(ustring), i_attName,   ("value"))

    PSTADE_INSTANCE(const(ustring), i_CharData,  ("&CharData"))
    PSTADE_INSTANCE(const(ustring), i_Reference, ("&Reference"))


} } // namespace pstade::lime


#endif
