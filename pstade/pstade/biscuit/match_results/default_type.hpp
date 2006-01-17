#pragma once

#include <boost/config.hpp> // for BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include "../parser/directive/no_captures.hpp"
#include "./match_results.hpp"
#include "./null_match_results.hpp"

namespace pstade { namespace biscuit {


namespace match_results_default_detail {

	template< class Parser >
	struct is_no_captures :
		boost::mpl::false_
	{ };

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

	template< class Parser >
	struct is_no_captures< no_captures<Parser> > :
		boost::mpl::true_
	{ };

#endif // !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

} // namespace match_results_default_detail


template< class Parser, class ParsingRange >
struct match_results_default
{
	typedef typename boost::mpl::if_< match_results_default_detail::is_no_captures<Parser>,
		null_match_results<ParsingRange>,
		match_results<ParsingRange>
	>::type type;
};


} } // namespace pstade::biscuit
