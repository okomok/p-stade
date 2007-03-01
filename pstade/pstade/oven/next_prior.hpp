#ifndef PSTADE_OVEN_NEXT_PRIOR_HPP
#define PSTADE_OVEN_NEXT_PRIOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iterator> // advance
#include <boost/iterator/iterator_categories.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace next_prior_detail {


    // 'boost::next_prior' doesn't know Traversal concept, so we define...

    template< class Iterator, class Difference > inline
    void advance(Iterator& it, Difference const& d, boost::random_access_traversal_tag)
    {
        it += d;
    }

    template< class Iterator, class Difference > inline
    void advance(Iterator& it, Difference const& d, boost::single_pass_traversal_tag)
    {
        std::advance(it, d);
    }


} // namespace next_prior_detail


struct op_next :
    callable<op_next>
{
    template< class Myself, class Iterator, class Difference = void >
    struct apply :
        pass_by_value<Iterator>
    { };

    template< class Result, class Iterator, class Difference >
    Result call(Iterator it, Difference& d) const
    {
        next_prior_detail::advance(it, d, typename boost::iterator_traversal<Iterator>::type());
        return it;
    }

    template< class Result, class Iterator >
    Result call(Iterator it) const
    {
        return ++it;
    }
};

PSTADE_CONSTANT(next, (op_next))


struct op_prior :
    callable<op_prior>
{
    template< class Myself, class Iterator, class Difference = void >
    struct apply :
        pass_by_value<Iterator>
    { };

    template< class Result, class Iterator, class Difference >
    Result call(Iterator it, Difference& d) const
    {
        next_prior_detail::advance(it, -d, typename boost::iterator_traversal<Iterator>::type());
        return it;
    }

    template< class Result, class Iterator >
    Result call(Iterator it) const
    {
        return --it;
    }
};

PSTADE_CONSTANT(prior, (op_prior))


// If 'pstade::compose' or 'lambda::bind' is slow to compile...


struct op_next_begin :
    callable<op_next_begin>
{
    template< class Myself, class Range, class Difference = void >
    struct apply :
        range_iterator<Range>
    { };

    template< class Result, class Range, class Difference >
    Result call(Range& rng, Difference& d) const
    {
        return next(boost::begin(rng), d);
    }

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return next(boost::begin(rng));
    }
};

PSTADE_CONSTANT(next_begin, (op_next_begin))


struct op_prior_end :
    callable<op_prior_end>
{
    template< class Myself, class Range, class Difference = void >
    struct apply :
        range_iterator<Range>
    { };

    template< class Result, class Range, class Difference >
    Result call(Range& rng, Difference& d) const
    {
        return prior(boost::end(rng), d);
    }

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return prior(boost::end(rng));
    }
};

PSTADE_CONSTANT(prior_end, (op_prior_end))


} } // namespace pstade::oven


#endif
