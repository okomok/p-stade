#ifndef PSTADE_SAUSAGE_DETAIL_TAG_OF_TYPE_HPP
#define PSTADE_SAUSAGE_DETAIL_TAG_OF_TYPE_HPP


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


namespace tag_of_detail {


	template< class T >
	struct customization_tag_is_not_specialized :
		boost::is_same<
			typename customization_tag<T>::type,
			default_way_tag
		>
	{ };


} // namespace tag_of_detail


template< class T >
struct tag_of
{
private:
	typedef typename remove_rcv<T>::type bare_t;

public:
	typedef typename
	boost::mpl::eval_if< 
		has_pstade_sausage_enumerable<T>,
		boost::mpl::identity<intrusive_way_tag>,
		boost::mpl::eval_if<
			boost::mpl::and_<
				tag_of_detail::customization_tag_is_not_specialized<T>,
				apple::is_boost_range<T>
			>,
			boost::mpl::identity<boost_range_tag>,
			customization_tag<bare_t>
		>
	>::type type;
};


} } } // namespace pstade::sausage::detail


#endif
