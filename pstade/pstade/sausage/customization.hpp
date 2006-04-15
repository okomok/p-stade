#ifndef PSTADE_SAUSAGE_CUSTOMIZATION_HPP
#define PSTADE_SAUSAGE_CUSTOMIZATION_HPP


// PStade.Sausage
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/identity.hpp>
#include "./detail/default_way_tag.hpp"


namespace pstade { namespace sausage {


template< class T >
struct customization_tag :
	boost::mpl::identity<detail::default_way_tag>
{ };


template< class T >
struct customization; // tag dispatch way
/*
{
	typedef my_arg_type argument_type;

	template< class My, class EnumFtor >
	EnumFtor enumerate(My& my, EnumFtor fun)
	{
		return ...
	}
}
*/


} } // namespace pstade::sausage


#endif
