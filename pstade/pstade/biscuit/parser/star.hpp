#ifndef PSTADE_BISCUIT_PARSER_STAR_HPP
#define PSTADE_BISCUIT_PARSER_STAR_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <pstade/debug.hpp>
#include <pstade/oven/range_iterator.hpp>
#include "./begin.hpp"
#include "./end.hpp"
#include "./eps.hpp"


namespace pstade { namespace biscuit {


namespace star_detail {


    template< class Parser >
    struct release
    {
        template< class State, class UserState >
        static bool parse(State& s, UserState& us)
        {
            for (;;) {
                if (!Parser::parse(s, us))
                    break;

                if (biscuit::state_is_end(s))
                    break;
            }

            return true;
        }
    };


    template< class Parser >
    struct debug
    {
        template< class State, class UserState >
        static bool parse(State& s, UserState& us)
        {
            typedef typename oven::range_iterator<State>::type iter_t;

            for (;;) {
                iter_t const marker = s.get_cur();

                if (!Parser::parse(s, us))
                    break;

                iter_t const cur = s.get_cur();
                if (marker == cur) {
                    BOOST_ASSERT(biscuit::state_is_end(s) &&
                        "Parser must advance on star-operation; 'end/eol' are the usual suspects,"
                        "or iterator's comparison operator is broken."
                    );
                }

                if (biscuit::state_is_end(s))
                    break;
            }

            return true;
        }
    };


    template< class Parser, class HasSideEffects >
    struct super_
    {
        typedef typename boost::mpl::if_<
            boost::mpl::or_< is_ndebug, HasSideEffects >,
            release<Parser>,
            debug<Parser>
        >::type type;
    };


} // namespace star_detail


template<
    class Parser,
    class HasSideEffects = boost::mpl::false_
>
struct star :
    star_detail::super_< Parser, HasSideEffects >::type
{ };


// meaningless
//
template< class HasSideEffects >
struct star< PSTADE_BISCUIT_NULLARY_PARSER(begin), HasSideEffects >;

template< class HasSideEffects >
struct star< PSTADE_BISCUIT_NULLARY_PARSER(end), HasSideEffects >;

template< class HasSideEffects >
struct star< PSTADE_BISCUIT_NULLARY_PARSER(eps), HasSideEffects >;


} } // namespace pstade::biscuit


#endif
