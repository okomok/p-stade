#ifndef PSTADE_KETCHUP_CRACK_ENTRY_SET_HPP
#define PSTADE_KETCHUP_CRACK_ENTRY_SET_HPP


// PStade.Ketchup
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../id.hpp"
#include "./entry_subset.hpp"
#include "./detail/handler_entry_set_declare.ipp"


namespace pstade { namespace ketchup {


template< class Derived >
struct crack_entry_set :
	crack_entry_subset
{
	#include "./detail/handler_entry_set.ipp"
};


} } // namespace pstade::ketchup

//#include "detail/handler_entry_set_undef.ipp"


#endif
