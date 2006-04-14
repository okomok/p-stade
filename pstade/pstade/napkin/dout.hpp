#ifndef PSTADE_NAPKIN_DOUT_HPP
#define PSTADE_NAPKIN_DOUT_HPP


// PStade.Napkin
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/sdk/windows.hpp>
#include <pstade/instance.hpp>


namespace pstade { namespace napkin {


namespace dout_detail {


	struct out
	{
		void operator<<(const char *psz) const
		{
			::OutputDebugStringA(psz);
		}

		void operator<<(const wchar_t *psz) const
		{
			::OutputDebugStringW(psz);
		}
	};


} // dout_detail


PSTADE_INSTANCE(const dout_detail::out, dout)


} } // namespace pstade::napkin


#endif
