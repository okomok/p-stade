#ifndef PSTADE_LIME_ATT_NAMES_HPP
#define PSTADE_LIME_ATT_NAMES_HPP


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


PSTADE_INSTANCE(const ustring, att_Name, (oven::sequence("<Name>"|oven::null_terminated)))
PSTADE_INSTANCE(const ustring, att_CharData, (oven::sequence("<CharData>"|oven::null_terminated)))


} } // namespace pstade::lime


#endif
