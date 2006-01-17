#pragma once

#include <pstade/overload.hpp>

namespace pstade { namespace tomato {


///////////////////////////////////////////////////////////////////////////////
// profile_initialize
//
template< class StringT, class Profile > inline
void profile_initialize(Profile& pr, const StringT& name)
{
	pstade_tomato_profile_initialize(pr, name, overload());
}


} } // namespace pstade::tomato


///////////////////////////////////////////////////////////////////////////////
// default
//
template< class StringT, class Profile > inline
void pstade_tomato_profile_initialize(Profile& pr, const StringT& name, ...)
{
	pr.pstade_tomato_profile_initialize(name);
}
