#pragma once

#include <cstddef>
#include <pstade/null_ptr.hpp>
#include <pstade/unused.hpp>
#include "../cast/boolean_cast.hpp"

namespace pstade { namespace tomato {


#if (_ATL_VER >= 0x0700)

	inline bool is_valid_address(const void *p, std::size_t nBytes, bool bReadWrite = true)
	{
		return tomato::boolean_cast<bool>(ATL::AtlIsValidAddress(p, nBytes, tomato::boolean_cast<BOOL>(bReadWrite)));
	}

#else

	inline bool is_valid_address(const void *p, std::size_t nBytes, bool bReadWrite = true)
	{
		// See: ATL7::AtlIsValidAddress

	#if !defined(_WIN32_WCE)
		return
			(p != pstade::null_ptr) &&
			!::IsBadReadPtr(p, nBytes) &&
			(!bReadWrite || !::IsBadWritePtr(const_cast<LPVOID>(p), nBytes))
		;
	#else
		pstade::unused(nBytes, bReadWrite);
		return
			(p != pstade::null_ptr)
		;
	#endif // !defined(_WIN32_WCE)
	}

#endif // (_ATL_VER >= 0x0700)


} } // namespace pstade::tomato
