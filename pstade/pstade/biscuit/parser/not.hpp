#pragma once

#include <boost/config.hpp> // for BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/range/result_iterator.hpp>
#include <pstade/assert.hpp>
#include <pstade/unused.hpp>
#include "../config/nullary_parser.hpp"
#include "../state/cur_guard.hpp"
#include "../state/increment.hpp"
#include "../state/is_end.hpp"
#include "./identity.hpp"

namespace pstade { namespace biscuit {


///////////////////////////////////////////////////////////////////////////////
// not_
//
template< class Parser >
struct not_ // one character parser
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		if (biscuit::state_is_end(s))
			return false;

		state_cur_guard<State> gd(s);

		if (Parser::parse(s, us))
		{
		#if defined(_DEBUG)
			typedef typename boost::range_result_iterator<State>::type iter_t;
			iter_t one_step_forward; { one_step_forward = gd.marker(); ++one_step_forward; }
			PSTADE_ASSERT(s.get_cur() == one_step_forward && "pstade::biscuit::not_ - not_ is defined only if one character parser.");
		#endif
			return false;
		}

		biscuit::state_increment(s);

		gd.dismiss();
		return true;
	}
};


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

	///////////////////////////////////////////////////////////////////////////////
	// not not_
	//
	template< class Parser >
	struct not_< not_<Parser> > :
		identity<Parser>
	{ };

#endif // !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)


} } // namespace pstade::biscuit
