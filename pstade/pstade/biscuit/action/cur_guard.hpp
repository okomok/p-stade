#pragma once

#include <boost/noncopyable.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/workaround/warning_no_copy_constructor.hpp>

// See: scope_guard
//   at 'Function Objects' of http://boost-consulting.com/vault/

namespace pstade { namespace biscuit {


template< class State >
struct state_cur_guard :
	private boost::noncopyable
{
	typedef typename boost::range_result_iterator<State>::type iter_t; 

	state_cur_guard(State& s) :
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

	PSTADE_WORKAROUND_WARNING_NO_COPY_CONSTRUCTOR(state_cur_guard)

private:
	State& m_state;
	iter_t const m_marker;
	bool m_dismissed;
};


} } // namespace pstade::biscuit
