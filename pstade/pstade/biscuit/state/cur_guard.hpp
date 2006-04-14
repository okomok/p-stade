#ifndef PSTADE_BISCUIT_STATE_CUR_GUARD_HPP
#define PSTADE_BISCUIT_STATE_CUR_GUARD_HPP


// PStade.Biscuit
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/noncopyable.hpp>
#include <boost/range/result_iterator.hpp>


// See: scope_guard
//   at 'Function Objects' of http://boost-consulting.com/vault/


namespace pstade { namespace biscuit {


template< class State >
struct state_cur_guard :
	private boost::noncopyable
{
	typedef typename boost::range_result_iterator<State>::type iter_t; 

	explicit state_cur_guard(State& s) :
		m_state(s), m_marker(s.get_cur()), m_dismissed(false)
	{ }

	~state_cur_guard()
	{
		if (!m_dismissed)
			m_state.set_cur(m_marker);
	}

	iter_t marker() const
	{ return m_marker; }

	void dismiss()
	{ m_dismissed = true; }

private:
	State& m_state;
	iter_t const m_marker;
	bool m_dismissed;
};


} } // namespace pstade::biscuit


#endif
