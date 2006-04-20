#ifndef PSTADE_DIET_ACCESS_HPP
#define PSTADE_DIET_ACCESS_HPP


// PStade.Diet
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace diet {


class access
{
public:
	template< class T > static
	bool detail_is_valid(const T& x)
	{
		return x.pstade_diet_is_valid();
	}

	template< class T, class OStream > static
	void detail_dump(const T& x, OStream& os)
	{
		x.pstade_diet_dump(os);
	}
};


} } // namespace pstade::diet


#endif
