#ifndef PSTADE_BISCUIT_PARSER_ERROR_EXPECT_HPP
#define PSTADE_BISCUIT_PARSER_ERROR_EXPECT_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/end.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/oven/iter_range.hpp>
#include "./parser_error.hpp"


namespace pstade { namespace biscuit {


template< int id, class Parser >
struct expect
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        typedef typename boost::range_result_iterator<State>::type iter_t;
        typedef typename oven::iter_range<iter_t> range_t;

        if (!Parser::parse(s, us)) {
            throw parser_error<range_t, int>(
                oven::make_iter_range(s.get_cur(), boost::end(s)), id
            );
        }

        return true;
    }
};


} } // namespace pstade::biscuit


#endif
