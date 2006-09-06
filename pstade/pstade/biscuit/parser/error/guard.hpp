#ifndef PSTADE_BISCUIT_PARSER_ERROR_GUARD_HPP
#define PSTADE_BISCUIT_PARSER_ERROR_GUARD_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include "./parser_error.hpp"


namespace pstade { namespace biscuit {


enum error_status
{
    error_fail,
    error_retry,
    error_accept,
    error_rethrow
};


template< class Parser, class HandlerT, class InfoT = int >
struct guard
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        typedef typename boost::range_result_iterator<State>::type iter_t;
        typedef typename boost::iterator_range<iter_t> range_t;

        iter_t const marker = s.get_cur();

        error_status es = error_retry;
        while (es == error_retry) {
            try {
                return Parser::parse(s, us);
            }
            catch (parser_error<range_t, InfoT>& e) {
                BOOST_ASSERT(s.get_cur() == marker && "non-exception-safe Parser found");
                s.set_cur(marker);

                es = HandlerT()(s, us, e.get_range(), e.get_info());
                switch (es)
                {
                    case error_fail:
                        return false;
                    case error_accept:
                        return true;
                    case error_rethrow:
                        throw;
                    case error_retry:
                        continue;
                    default:
                        BOOST_ASSERT(false && "undefined code");
                }
            } // catch
        } // while

        return false;
    }
};


} } // namespace pstade::biscuit


#endif
