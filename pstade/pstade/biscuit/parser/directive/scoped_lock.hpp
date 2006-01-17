#pragma once

namespace pstade { namespace biscuit {


template< class MutexFtor >
struct scoped_lock_type
{
	typedef typename MutexFtor::scoped_lock_type type;
};

template< class Parser, class MutexFtor >
struct scoped_lock
{
	template< class State, class UserState >
	static bool parse(State& s, UserState& us)
	{
		typedef typename scoped_lock_type<MutexFtor>::type lock_t;

		lock_t lock(MutexFtor()(us));
		return Parser::parse(s, us);
	}
};


} } // namespace pstade::biscuit
