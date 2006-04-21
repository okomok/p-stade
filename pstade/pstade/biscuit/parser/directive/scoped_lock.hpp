#ifndef PSTADE_BISCUIT_PARSER_DIRECTIVE_SCOPED_LOCK_HPP
#define PSTADE_BISCUIT_PARSER_DIRECTIVE_SCOPED_LOCK_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


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


#endif
