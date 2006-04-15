#ifndef PSTADE_SAUSAGE_ENUMERATE_ARGUMENT_TYPE_HPP
#define PSTADE_SAUSAGE_ENUMERATE_ARGUMENT_TYPE_HPP


// PStade.Sausage
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./customization.hpp"
#include "./detail/tag_of_type.hpp"


namespace pstade { namespace sausage {


template< class Enumerable >
struct enumerate_argument
{
private:
	typedef typename detail::tag_of<Enumerable>::type tag_t;
	typedef customization<tag_t> cust_t;

public:
	typedef typename cust_t::template enumerate_argument<Enumerable>::type type;
};


} } // namespace pstade::sausage


#endif
