#ifndef PSTADE_BISCUIT_PARSER_AFTER_HPP
#define PSTADE_BISCUIT_PARSER_AFTER_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Unstable


#include <algorithm> // distance
#include <cstddef>   // ptrdiff_t
#include <iterator>  // advance
#include <boost/iterator/iterator_categories.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/static_assert.hpp>
#include <pstade/unused.hpp>
#include "../algorithm/match.hpp"
#include "./not_fwd.hpp"


namespace pstade { namespace biscuit {


namespace after_detail {


    template< class Parser, class State, class UserState, class Difference >
    bool match(State& s, UserState& us,
        Difference len, Difference begin_to_cur,
        boost::forward_traversal_tag)
    {
        typedef typename boost::range_result_iterator<State>::type iter_t;
        typedef typename boost::range_difference<State>::type diff_t;

        iter_t first = boost::begin(s);
        std::advance(first, begin_to_cur - len);

        return biscuit::match<Parser>(
            boost::make_iterator_range(first, s.get_cur()),
            us
        );
    }


    template< class Parser, class State, class UserState, class Difference >
    bool match(State& s, UserState& us,
        Difference len, Difference begin_to_cur,
        boost::bidirectional_traversal_tag)
    {
        typedef typename boost::range_result_iterator<State>::type iter_t;

        iter_t first = s.get_cur();
        std::advance(first, -len);

        pstade::unused(begin_to_cur);

        return biscuit::match<Parser>(
            boost::make_iterator_range(first, s.get_cur()),
            us
        );
    }


} // namespace after_detail


template< class Parser, std::ptrdiff_t len >
struct after
{
    BOOST_STATIC_ASSERT(0 <= len);

    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        typedef typename boost::range_result_iterator<State>::type iter_t;
        typedef typename boost::iterator_traversal<iter_t>::type trv_t;
        typedef typename boost::range_difference<State>::type diff_t;

        diff_t begin_to_cur = std::distance(boost::begin(s), s.get_cur());
        if (begin_to_cur < len)
            return false;

        return after_detail::match<Parser>(s, us, len, begin_to_cur, trv_t());
    }
};


// TODO: not after
//
template< class Parser, std::ptrdiff_t len >
struct not_< after<Parser, len> >;


} } // namespace pstade::biscuit


#endif
