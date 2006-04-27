#ifndef PSTADE_LIME_INTRINSIC_HPP
#define PSTADE_LIME_INTRINSIC_HPP


// PStade.Lime
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/instance.hpp>
#include <pstade/oven/null_terminate_range.hpp>
#include <pstade/oven/sequence_cast.hpp>
#include "./ustring.hpp"


namespace pstade { namespace lime {


PSTADE_INSTANCE(const ustring, i_CharData,
    (oven::sequence_cast<ustring>("&CharData"|oven::null_terminated))
)

PSTADE_INSTANCE(const ustring, i_Reference,
    (oven::sequence_cast<ustring>("&Reference"|oven::null_terminated))
)


PSTADE_INSTANCE(const ustring, i_attName,
    (oven::sequence_cast<ustring>("value"|oven::null_terminated))
)


} } // namespace pstade::lime


#endif
