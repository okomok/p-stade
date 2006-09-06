#ifndef PSTADE_BISCUIT_STATE_PARSE_HPP
#define PSTADE_BISCUIT_STATE_PARSE_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/optional.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/result_iterator.hpp>


namespace pstade { namespace biscuit {


template< class Range >
struct optional_iterator
{
    typedef boost::optional<
        typename boost::range_result_iterator<Range>::type
    > type;
};


namespace state_parse_detail {


    template< class State, class Range >
    typename optional_iterator<State>::type
    aux(State& s, Range& r)
    {
        typedef typename boost::range_result_iterator<State>::type siter_t;
        typedef typename boost::range_result_iterator<Range>::type riter_t;
        typedef boost::optional<siter_t> opt_t;

        siter_t sit(s.get_cur()), slast(boost::end(s));
        riter_t rit(boost::begin(r)), rlast(boost::end(r));

        for (; sit != slast && rit != rlast; ++sit, ++rit) {
            if (*sit != *rit)
                return opt_t();
        }

        if (rit != rlast) // not matched
            return opt_t();

        return opt_t(sit);
    }


} // namespace state_parse_detail


template< class State, class Range > inline
typename optional_iterator<State>::type
state_parse(State& s, Range& r)
{
    return state_parse_detail::aux(s, r);
}


template< class State, class Range > inline
typename optional_iterator<State>::type
state_parse(State& s, Range const& r)
{
    return state_parse_detail::aux(s, r);
}


} } // namespace pstade::biscuit


#endif
