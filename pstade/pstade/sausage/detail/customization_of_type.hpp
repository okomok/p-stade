#ifndef PSTADE_SAUSAGE_DETAIL_CUSTOMIZATION_OF_TYPE_HPP
#define PSTADE_SAUSAGE_DETAIL_CUSTOMIZATION_OF_TYPE_HPP


// PStade.Sausage
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/apple/is_boost_range.hpp>
#include <pstade/has_xxx.hpp>
#include "../customization.hpp"


namespace pstade { namespace sausage { namespace detail {


PSTADE_HAS_XXX(pstade_sausage_enumerate_argument_type)


template< class T >
struct customization_tag_is_specialized :
	boost::mpl::not_<
		boost::is_same<typename customization_tag<T>::type, T>
	>
{ };


template< class T >
struct customization_of
{
private:
	typedef typename boost::remove_cv<T>::type bare_t;

	typedef typename
	boost::mpl::eval_if< customization_tag_is_specialized<bare_t>,
		customization_tag<bare_t>,
		boost::mpl::eval_if< has_pstade_sausage_enumerate_argument_type<bare_t>,
			boost::mpl::identity<intrusive_way_tag>,
			boost::mpl::eval_if< apple::is_boost_range<bare_t>,
				boost::mpl::identity<boost_range_tag>,
				customization_tag<bare_t>
			>
		>
	>::type tag_t;

public:
	typedef customization<tag_t> type;
};


} } } // namespace pstade::sausage::detail


#endif
