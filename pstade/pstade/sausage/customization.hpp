#ifndef PSTADE_SAUSAGE_CUSTOMIZATION_HPP
#define PSTADE_SAUSAGE_CUSTOMIZATION_HPP


// PStade.Sausage
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/foreach.hpp>
#include <boost/iterator/iterator_traits.hpp> // iterator_reference
#include <boost/mpl/identity.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include "./access.hpp"


namespace pstade { namespace sausage {


struct intrusive_way_tag { };
struct boost_range_tag { };


template< class T >
struct customization_tag :
	boost::mpl::identity<T>
{ };


template< class TagT >
struct customization;


// predefined customizations
//

template< >
struct customization<intrusive_way_tag>
{
	template< class T >
	struct enumerate_argument
	{
		// insensitive to const-qualification
		typedef typename T::pstade_sausage_enumerate_argument_type type;
	};

	template< class Argument, class T, class EnumFtor >
	EnumFtor enumerate(T& x, EnumFtor fun)
	{
		return access::template detail_enumerate<Argument>(x, fun);
	}
};


template< >
struct customization<boost_range_tag>
{
	template< class Range >
	struct enumerate_argument
	{
		typedef typename boost::range_result_iterator<Range>::type iter_t;
		typedef typename boost::iterator_reference<iter_t>::type type;
	};

	template< class Argument, class Range, class EnumFtor >
	EnumFtor enumerate(Range& rng, EnumFtor fun)
	{
		BOOST_FOREACH (Argument arg, rng) {
			if (!fun(arg))
				break;
		}

		return fun;
	}
};


} } // namespace pstade::sausage


#endif
