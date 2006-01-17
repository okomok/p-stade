#pragma once


// Note: I guess most of structures need not to be zero-initialized.

namespace pstade { namespace tomato {


// To be "= { 0 };" or not to be for consistency.
template< class AggregateT > inline
AggregateT& zero_initialize(AggregateT& x)
{
	memset(&x, 0, sizeof(AggregateT));
	return x;
}


} } // namespace pstade::tomato
