#ifndef PSTADE_BISCUIT_PARSER_STAR_HPP
#define PSTADE_BISCUIT_PARSER_STAR_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/is_debug.hpp>
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
            for (;;) {
                typedef typename boost::range_result_iterator<State>::type iter_t;
                iter_t const marker = s.get_cur();

                if (!Parser::parse(s, us))
                    break;

                iter_t const cur = s.get_cur();
                if (marker == cur) {
                    BOOST_ASSERT(false &&
                        "Parser must advance on star-operation; 'end/eol' are the usual suspects,"
                        "or iterator's comparison operator is broken."
                    );
                }
            }

            return true;
        }
    };


    template< class Parser, class NoSideEffects >
    struct super_
    {
        typedef typename boost::mpl::if_<
            boost::mpl::and_< is_debug<>, NoSideEffects >,
            debug<Parser>,
            release<Parser>
        >::type type;
    };


} // namespace star_detail


template<
    class Parser,
    class NoSideEffects = boost::mpl::true_
>
struct star :
    star_detail::super_< Parser, NoSideEffects >::type
{ };


// meaningless
//
template< class NoSideEffects >
struct star< PSTADE_BISCUIT_NULLARY_PARSER(begin), NoSideEffects >;

template< class NoSideEffects >
struct star< PSTADE_BISCUIT_NULLARY_PARSER(end), NoSideEffects >;

template< class NoSideEffects >
struct star< PSTADE_BISCUIT_NULLARY_PARSER(eps), NoSideEffects >;


} } // namespace pstade::biscuit


#endif
