#ifndef PSTADE_SAUSAGE_DETAIL_TAG_DISPATCH_WAY_HPP
#define PSTADE_SAUSAGE_DETAIL_TAG_DISPATCH_WAY_HPP


// PStade.Sausage
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>
#include "../customization.hpp"
#include "./default_way_tag.hpp"
#include "./tag_of_type.hpp"


namespace pstade { namespace sausage { namespace detail {


struct tag_dispatch_way
{
	template< class T, class EnumFtor > static
	EnumFtor call(T& x, EnumFtor fun)
	{
		typedef customization<typename tag_of<T>::type> cust_t;
		return cust_t::enumerate(x, fun);
	}

	typedef tag_dispatch_way type;
};


template< class T >
struct tag_dispatch_way_argument
{
	typedef customization<typename tag_of<T>::type> cust_t;
	typedef typename cust_t::argument_type type;
};


template< class T >
struct is_tag_dispatch_way :
	boost::mpl::not_<
		boost::is_same<typename tag_of<T>::type, default_way_tag>
	>
{ };


} } } // namespace pstade::sausage::detail


#endif
