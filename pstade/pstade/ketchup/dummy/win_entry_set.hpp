#pragma once

#include "./win_entry_subset.hpp"

namespace pstade { namespace ketchup {


template< class Derived >
struct win_entry_set :
	win_entry_subset
{
	#include "./detail/handler_entry_set.ipp"
};


} } // namespace pstade::ketchup
