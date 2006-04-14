#ifndef PSTADE_SAUSAGE_DETAIL_TAG_OF_TYPE_HPP
#define PSTADE_SAUSAGE_DETAIL_TAG_OF_TYPE_HPP


// PStade.Sausage
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/remove_rcv.hpp>
#include "../customization.hpp"


namespace pstade { namespace sausage { namespace detail {


template< class T >
struct tag_of :
	customization_tag<
		typename remove_rcv<T>::type
	>
{ };


} } } // namespace pstade::sausage::detail


#endif
