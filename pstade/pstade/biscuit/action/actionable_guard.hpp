#pragma once

#include <boost/noncopyable.hpp>

namespace pstade { namespace biscuit {


template< class State >
struct state_actionable_guard :
	private boost::noncopyable
{
	state_actionable_guard(State& s, bool act) :
		m_state(s), m_prev(s.is_actionable())
	{ m_state.set_actionable(act); }

	~state_actionable_guard()
	{ m_state.set_actionable(m_prev); }

private:
	State& m_state;
	bool const m_prev;
};


} } // namespace pstade::biscuit
