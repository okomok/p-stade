#pragma once

#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/assert.hpp>
#include "./parser_error.hpp"

namespace pstade { namespace biscuit {


///////////////////////////////////////////////////////////////////////////////
// error_status
//
enum error_status
{
	error_fail,
	error_retry,
	error_accept,
	error_rethrow
};

///////////////////////////////////////////////////////////////////////////////
// guard
//
template< class Parser, class HandlerT, class InfoT = int >
struct guard
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		typedef typename boost::range_result_iterator<State>::type iter_t;
		typedef typename boost::iterator_range<iter_t> range_t;

		iter_t const marker = s.get_cur();

		error_status es = error_retry;
		while (es == error_retry) {
			try {
				return Parser::parse(s, us);
			}
			catch (parser_error<range_t, InfoT>& e) {
				PSTADE_ASSERT(s.get_cur() == marker && "pstade::biscuit::guard - Not-exception-safe Parser is found.");
				s.set_cur(marker);

				es = HandlerT()(s, us, e.get_range(), e.get_info());
				switch (es)
				{
					case error_fail:
						return false;
					case error_accept:
						return true;
					case error_rethrow:
						throw;
					case error_retry:
						continue;
					default:
						PSTADE_ASSERT(false && "pstade::biscuit::guard - An undefined code returns from handler.");
				}
			} // catch
		} // while

		return false;
	}
};


} } // namespace pstade::biscuit
