#ifndef PSTADE_BISCUIT_PARSER_CAPTURE_BACKREF_HPP
#define PSTADE_BISCUIT_PARSER_CAPTURE_BACKREF_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <pstade/unused.hpp>
#include "../../match_results/find_backref.hpp"


namespace pstade { namespace biscuit {


template< int id >
struct backref
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        typedef typename boost::range_result_iterator<State>::type iter_t;
        iter_t it = s.get_cur();
        iter_t last = boost::end(s);

        typedef boost::iterator_range<iter_t> subrng_t;
        subrng_t subrng;
        if (!biscuit::find_backref(s.results(), id, subrng))
            return true; // common sense?

        typedef typename boost::range_const_iterator<subrng_t>::type subrng_citer_t;
        subrng_citer_t it_ = boost::const_begin(subrng);
        subrng_citer_t last_ = boost::const_end(subrng);

        for (; it != last && it_ != last_; ++it, ++it_) {
            if (*it != *it_)
                return false;
        }

        if (it_ != last_) // not matched
            return false;

        s.set_cur(it);

        pstade::unused(us);
        return true;
    }
};


} } // namespace pstade::biscuit


#endif
