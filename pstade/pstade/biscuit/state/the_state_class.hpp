#ifndef PSTADE_BISCUIT_STATE_THE_STATE_CLASS_HPP
#define PSTADE_BISCUIT_STATE_THE_STATE_CLASS_HPP


// PStade.Biscuit
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/noncopyable.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/oven/begin_end.hpp>
#include <pstade/oven/sub_range_base_type.hpp>


namespace pstade { namespace biscuit {


struct the_state_class
{
	typedef the_state_class type;

	template< class ParsingRange, class MatchResults >
	struct state :
		private boost::noncopyable,
		oven::sub_range_base<ParsingRange>::type
	{
	private:
		typedef typename oven::sub_range_base<ParsingRange>::type super_t;
		typedef typename boost::range_result_iterator<super_t>::type iter_t;

	public:
		// for state metafunctions
		//
		typedef the_state_class state_class_type;
		typedef ParsingRange parsing_range_type;
		typedef MatchResults match_results_type;

		// accessors
		//
		iter_t get_cur() const { return m_cur; }
		void set_cur(iter_t it) { m_cur = it; }
		MatchResults& results() { return m_results; }
		bool is_actionable() const { return m_actionable; }
		void set_actionable(bool act) { m_actionable = act; }

		// structors
		//
		template< class ForwardRange2 >
		explicit state(ForwardRange2& other, MatchResults& results, bool act = true) :
			super_t(oven::begin(other), oven::end(other)),
			m_results(results), m_actionable(act)
		{
			m_cur = oven::begin(*this);
		}

	private:
		iter_t m_cur;
		MatchResults& m_results;
		bool m_actionable;
	};

	// Note:
	//   apply itself must be a lightweight type,
	//   because 'apply' could be a base class for Boost.MPL.
	template< class ParsingRange, class MatchResults >
	struct apply
	{
		typedef state<ParsingRange, MatchResults> type;
	};

};


} } // namespace pstade::biscuit


#endif
