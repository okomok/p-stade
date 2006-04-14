#ifndef PSTADE_SAUSAGE_ACCESS_HPP
#define PSTADE_SAUSAGE_ACCESS_HPP


// PStade.Sausage
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace sausage {


class access
{
public:
	template< class T, class EnumFtor > static
	EnumFtor detail_call(T& x, EnumFtor fun)
	{
		return x.pstade_sausage_enumerate(fun);
	}
};


} } // namespace pstade::sausage


#endif
