#ifndef PSTADE_BISCUIT_ACTION_OUTPUT_ACTION_HPP
#define PSTADE_BISCUIT_ACTION_OUTPUT_ACTION_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/foreach.hpp>
#include <pstade/oven/range_reference.hpp>


namespace pstade { namespace biscuit {


struct output_action
{
    template< class ParsingSubRange, class UserState >
    void operator()(ParsingSubRange& rng, UserState& out) const
    {
        typedef typename oven::range_reference<ParsingSubRange>::type ref_t;
        BOOST_FOREACH (ref_t v, rng) {
            out << v;
        }
    }
};


} } // namespace pstade::biscuit


#endif
