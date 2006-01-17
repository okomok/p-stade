#pragma once

#include <pstade/overload.hpp>

namespace pstade { namespace stove {


template< class Sequence, class Iter > inline
void erase(Sequence& seq, Iter first, Iter last)
{
	pstade_stove_erase(seq, first, last, overload());
}


} } // namespace pstade::stove


// default
template< class StlSequence, class Iter > inline
void pstade_stove_erase(StlSequence& seq, Iter first, Iter last, ...)
{
	seq.erase(first, last);
}
