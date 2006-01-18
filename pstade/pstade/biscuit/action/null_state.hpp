#pragma once

namespace pstade { namespace biscuit {


struct null_state_type
{ };

namespace {
	// Reason why: static
	//   If static is missing, VC7.1 preprocessed header is sometimes broken.

	//   For reference syntax, it is not const.
	static null_state_type null_state;
}


} } // namespace pstade::biscuit
