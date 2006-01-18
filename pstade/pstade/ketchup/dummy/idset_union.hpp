#pragma once


namespace pstade { namespace ketchup {


template< class IDs0, class IDs1 >
struct idset_union
{
	static bool contains(UINT id)
	{
		if (IDs0::contains(id)) { return true; }
		if (IDs1::contains(id)) { return true; }
		
		return false;
	}
};


} } // namespace pstade::ketchup
