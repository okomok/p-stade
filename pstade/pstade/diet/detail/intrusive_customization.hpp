#ifndef PSTADE_DIET_DETAIL_INTRUSIVE_CUSTOMIZATION_HPP
#define PSTADE_DIET_DETAIL_INTRUSIVE_CUSTOMIZATION_HPP


// PStade.Diet
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../access.hpp"
#include "./intrusive_tag.hpp"


namespace pstade { namespace diet { namespace customization {


	template< >
	struct point<detail::intrusive_tag>
	{
		template< class T >
		bool is_valid(const T& x)
		{
			return access::detail_is_valid(x);
		}

		template< class T, class OStream >
		void dump(const T& x, OStream& os)
		{
			access::detail_dump(x, os);
		}
	};


} } } // namespace pstade::diet::customization


#endif
