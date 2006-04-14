#ifndef PSTADE_SAUSAGE_DETAIL_DEFAULT_WAY_HPP
#define PSTADE_SAUSAGE_DETAIL_DEFAULT_WAY_HPP


// PStade.Sausage
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/overload.hpp>
#include "../enumerate_argument_impl_fwd.hpp"


namespace pstade { namespace sausage { namespace detail {


struct default_way
{
	template< class T, class EnumFtor > static
	EnumFtor call(T& x, EnumFtor fun)
	{
		return pstade_sausage_enumerate(x, fun, overload());
	}

	typedef default_way type;
};


template< class T >
struct default_way_argument
{
	typedef typename enumerate_argument_impl<T>::type type;
};


} } } // namespace pstade::sausage::detail


#endif
