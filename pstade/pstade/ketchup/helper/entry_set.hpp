#ifndef PSTADE_KETCHUP_HELPER_ENTRY_SET_HPP
#define PSTADE_KETCHUP_HELPER_ENTRY_SET_HPP


// PStade.Ketchup
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./entry_subset.hpp"


namespace pstade { namespace ketchup {


template< class Derived >
struct helper_entry_set :
    helper_entry_subset
{ };


} } // namespace pstade::ketchup


#endif
