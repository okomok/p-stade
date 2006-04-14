#ifndef PSTADE_BISCUIT_PARSER_DYNAMIC_CONTROL_SEQ_RANGE_HPP
#define PSTADE_BISCUIT_PARSER_DYNAMIC_CONTROL_SEQ_RANGE_HPP


// PStade.Biscuit
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/functional.hpp> // unary_traits
#include <boost/range/begin.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/range/end.hpp>
#include <boost/type_traits/remove_reference.hpp>


namespace pstade { namespace biscuit {


// See: boost::starts_with
//   combination of starts_with and std::advance is easier,
//   but std::advance is somewhat redundant.
//
template< class RangeFtor >
struct seq_range
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		typedef typename boost::range_result_iterator<State>::type iter_t;
		iter_t it = s.get_cur();
		iter_t last = boost::end(s);

		typedef typename boost::unary_traits<RangeFtor>::result_type rng_t;
		typedef typename boost::remove_reference<rng_t>::type rng_t_;
		typedef typename boost::range_const_iterator<rng_t_>::type rng_citer_t;

		RangeFtor f; // non-temporary so that rng_t can be reference to its member.
		rng_t rng = f(us);
		rng_citer_t it_ = boost::const_begin(rng);
		rng_citer_t last_ = boost::const_end(rng);

		for (; it != last && it_ != last_; ++it, ++it_) {
			if (*it != *it_)
				return false;
		}

		if (it_ != last_) // not matched
			return false;

		s.set_cur(it);
		return true;
	}
};


} } // namespace pstade::biscuit


#endif
