#ifndef PSTADE_BISCUIT_ACTION_NULL_ACTION_HPP
#define PSTADE_BISCUIT_ACTION_NULL_ACTION_HPP


// PStade.Biscuit
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace biscuit {


struct null_action
{
	template< class ParsingSubRange, class UserState >
	void operator()(ParsingSubRange&, UserState&) const
	{ }
};


} } // namespace pstade::biscuit


#endif
