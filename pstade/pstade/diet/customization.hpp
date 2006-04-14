#ifndef PSTADE_DIET_CUSTOMIZATION_HPP
#define PSTADE_DIET_CUSTOMIZATION_HPP


// PStade.Diet
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/identity.hpp>
#include "./detail/intrusive_tag.hpp"
#include "./detail/tag_impl.hpp"


namespace pstade { namespace diet { namespace customization {


	template< class T >
	struct tag :
		detail::tag_impl<T>
	{ };


	template< class Tag >
	struct point;


	// utilities
	//
	template< class Tag >
	struct as :
		boost::mpl::identity<Tag>
	{ };

	typedef detail::intrusive_tag
	intrusive_tag;


} } } // namespace pstade::diet::customization


#endif
