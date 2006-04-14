#ifndef PSTADE_DIET_DETAIL_DEFAULT_CUSTOMIZATION_HPP
#define PSTADE_DIET_DETAIL_DEFAULT_CUSTOMIZATION_HPP


// PStade.Diet
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/diet/customization.hpp>
#include <pstade/overload.hpp>
#include "./default_tag.hpp"


namespace pstade { namespace diet {


namespace default_customization_detail {


	// adl layer
	//
	template< class T > inline
	bool pstade_diet_is_valid(const T& x)
	{
		// global layer
		//
		return pstade_diet_is_valid(x, overload());
	}

	template< class T, class OStream > inline
	void pstade_diet_dump(const T& x, OStream& os)
	{
		pstade_diet_dump(x, os, overload());
	}


} // namespace default_customization_detail


namespace customization {


	template< >
	struct point<detail::default_tag>
	{
		template< class T >
		bool is_valid(const T& x)
		{
			// adl layer
			//
			using namespace default_customization_detail;
			return pstade_diet_is_valid(x);
		}

		template< class T, class OStream >
		void dump(const T& x, OStream& os)
		{
			using namespace default_customization_detail;
			pstade_diet_dump(x, os);
		}
	};


} // namespace customization


} } // namespace pstade::diet


#endif
