#pragma once

#include <pstade/overload.hpp>

namespace pstade { namespace stove {


template< class Sequence, class ValueT > inline
void push_back(Sequence& seq, const ValueT& val)
{
	pstade_stove_push_back(seq, val, overload());
}


} } // namespace pstade::stove


// default
template< class StlSequence, class ValueT > inline
void pstade_stove_push_back(StlSequence& seq, const ValueT& val, ...)
{
	seq.push_back(val);
}
