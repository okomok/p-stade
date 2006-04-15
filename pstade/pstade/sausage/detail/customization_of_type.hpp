#ifndef PSTADE_SAUSAGE_DETAIL_CUSTOMIZATION_OF_TYPE_HPP
#define PSTADE_SAUSAGE_DETAIL_CUSTOMIZATION_OF_TYPE_HPP


// PStade.Sausage
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/and.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/apple/is_boost_range.hpp>
#include <pstade/remove_rcv.hpp>
#include "../customization.hpp"
#include "./has_pstade_sausage_enumerable.hpp"


namespace pstade { namespace sausage { namespace detail {


namespace customization_of_detail {


	template< class T >
	struct customization_tag_is_not_specialized :
		boost::is_same<
			typename customization_tag<T>::type,
			default_way_tag
		>
	{ };


} // namespace customization_of_detail


template< class T >
struct customization_of
{
private:
	typedef typename
	boost::mpl::eval_if< 
		has_pstade_sausage_enumerable<T>,
		boost::mpl::identity<intrusive_way_tag>,
		boost::mpl::eval_if<
			boost::mpl::and_<
				customization_of_detail::customization_tag_is_not_specialized<T>,
				apple::is_boost_range<T>
			>,
			boost::mpl::identity<boost_range_tag>,
			customization_tag<T>
		>
	>::type tag_t;

public:
	typedef customization<tag_t> type;
};


} } } // namespace pstade::sausage::detail


#endif
