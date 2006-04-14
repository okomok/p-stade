#ifndef PSTADE_DIET_DETAIL_TAG_IMPL_HPP
#define PSTADE_DIET_DETAIL_TAG_IMPL_HPP


// PStade.Diet
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include "./default_tag.hpp"
#include "./has_pstade_diet_diagnostic.hpp"
#include "./has_pstade_diet_tag.hpp"
#include "./intrusive_tag.hpp"


namespace pstade { namespace diet { namespace detail {


template< class T >
struct inner_tag_of
{
	typedef typename T::pstade_diet_tag type;
};


template< class T >
struct tag_impl :
	boost::mpl::eval_if<has_pstade_diet_tag<T>,
		inner_tag_of<T>,
		boost::mpl::eval_if< has_pstade_diet_diagnostic<T>,
			boost::mpl::identity<intrusive_tag>,
			boost::mpl::identity<default_tag>
		>
	>
{ };


} } } // namespace pstade::diet::detail


#endif
