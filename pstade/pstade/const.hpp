#pragma once

// See:
//  http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2004/n1674.pdf


namespace pstade {


///////////////////////////////////////////////////////////////////////////////
// const_
//
template< class T > inline
const T& const_(const T& x)
{
	return x;
}


namespace const_detail {

	struct range_adaptor_type
	{ };

	template< class T > inline
	const T& operator|(const T& x, range_adaptor_type)
	{
		return pstade::const_(x);
	}

} // namespace const_detail


///////////////////////////////////////////////////////////////////////////////
// const_qualified
//

namespace {

static // is required for a legacy "stdafx.h".
const const_detail::range_adaptor_type const_qualified = const_detail::range_adaptor_type();

} // namespace anonymous


} // namespace pstade
