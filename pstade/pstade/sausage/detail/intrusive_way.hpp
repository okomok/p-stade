#ifndef PSTADE_SAUSAGE_DETAIL_INTRUSIVE_WAY_HPP
#define PSTADE_SAUSAGE_DETAIL_INTRUSIVE_WAY_HPP


// PStade.Sausage
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../access.hpp"


namespace pstade { namespace sausage { namespace detail {


struct intrusive_way
{
	template< class T, class EnumFtor > static
	EnumFtor call(T& x, EnumFtor fun)
	{
		return access::detail_call(x, fun);
	}

	typedef intrusive_way type;
};


template< class T >
struct intrusive_way_argument
{
	typedef typename T::pstade_sausage_enumerate_argument_type type;
};


} } } // namespace pstade::sausage::detail


#endif
