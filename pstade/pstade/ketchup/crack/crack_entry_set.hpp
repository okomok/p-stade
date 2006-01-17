#pragma once

#include "../id.hpp"
#include "./crack_entry_subset.hpp"
#include "./detail/handler_entry_set_declare.ipp"

namespace pstade { namespace ketchup {


template< class Derived>
struct crack_entry_set :
	crack_entry_subset
{
	#include "./detail/handler_entry_set.ipp"
};


} } // namespace pstade::ketchup

//#include "detail/handler_entry_set_undef.ipp"
