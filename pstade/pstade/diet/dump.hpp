#ifndef PSTADE_DIET_DUMP_HPP
#define PSTADE_DIET_DUMP_HPP


// PStade.Diet
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/enable_if.hpp>
#include <boost/foreach.hpp>
#include <boost/iterator/iterator_traits.hpp> // iterator_reference
#include <boost/mpl/if.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/apple/is_boost_range.hpp>
#include <pstade/overload.hpp>
#include "./access.hpp"
#include "./detail/has_pstade_diagnostic.hpp"


namespace pstade { namespace diet {


namespace dump_detail {


	struct member_function
	{
		template< class T, class OStream > static
		void call(const T& x, OStream& os)
		{
			access::detail_dump(x, os);
		}
	};


	template< class T, class OStream > inline
	void pstade_diet_dump(const T& x, OStream& os)
	{
		pstade_diet_dump(x, os, pstade::overload());
	}

	struct adl_customization
	{
		template< class T, class OStream > static
		void call(const T& x, OStream& os)
		{
			pstade_diet_dump(x, os);
		}
	};


} // namespace dump_detail


template< class Diagnostic, class OStream > inline
void dump(const Diagnostic& dg, OStream& os)
{
    typedef typename
    boost::mpl::if_< detail::has_pstade_diet_diagnostic<Diagnostic>,
        dump_detail::member_function,
        dump_detail::adl_customization
    >::type impl_t;

    return impl_t::call(dg, os);
}


} } // namespace pstade::diet


// predefined customizations
//

template< class Range, class OStream > inline
typename boost::enable_if<pstade::apple::is_boost_range<Range>, void>::type
pstade_diet_dump(const Range& rng, OStream& os, pstade::overload)
{
	os << "<range>";

	typedef typename boost::range_const_iterator<Range>::type iter_t;
	typedef typename boost::iterator_reference<iter_t>::type ref_t;
	BOOST_FOREACH (ref_t x, rng) {
		pstade::diet::dump(x, os);
	}

	os << "</range>";
}


#endif
