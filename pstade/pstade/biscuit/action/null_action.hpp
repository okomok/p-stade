#pragma once

namespace pstade { namespace biscuit {


struct null_action
{
	template< class ParsingSubRange, class UserState >
	void operator()(ParsingSubRange&, UserState&) const
	{ }
};


} } // namespace pstade::biscuit
