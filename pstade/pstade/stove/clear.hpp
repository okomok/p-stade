#pragma once

// Optional

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/overload.hpp>

namespace pstade { namespace stove {


template< class Sequence > inline
void clear(Sequence& seq)
{
	pstade_stove_clear(seq, overload());
}


} } // namespace pstade::stove


// default
template< class StlSequence > inline
void pstade_stove_clear(StlSequence& seq, ...)
{
	seq.erase(boost::begin(seq), boost::end(seq));
}
