#ifndef PSTADE_OVEN_ADJACENT_FILTERED_HPP
#define PSTADE_OVEN_ADJACENT_FILTERED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This range is Constant;
// the iteration depends on the "previous" values.


#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./read.hpp"
#include "./successors.hpp"


namespace pstade { namespace oven {


namespace adjacent_filtered_detail {


    namespace here = adjacent_filtered_detail;


    template< class Iterator, class Predicate >
    Iterator filter_aux(Iterator first, Iterator last, Predicate pred,
        boost::forward_traversal_tag)
    {
        Iterator next = first;
        while (++next != last) {
            if (pred(read(first), read(next)))
                break;
        }

        return next;
    }

    template< class Iterator, class Predicate >
    Iterator filter_aux(Iterator next, Iterator last, Predicate pred,
        boost::single_pass_traversal_tag)
    {
        typename boost::iterator_value<Iterator>::type value = read(next);
        while (++next != last) {
            if (pred(value, read(next)))
                break;
        }

        return next;
    }


    template< class BinaryPred >
    struct filter
    {
        typedef filter is_constant;

        template< class Iterator>
        Iterator operator()(Iterator first, Iterator last) const
        {
            return here::filter_aux(first, last, m_pred,
                typename boost::iterator_traversal<Iterator>::type());
        }

        explicit filter()
        { }

        explicit filter(BinaryPred pred) :
            m_pred(pred)
        { }

    private:
        BinaryPred m_pred;
    };


    template< class Range, class BinaryPred >
    struct baby
    {
        typedef typename
            pass_by_value<BinaryPred>::type
        pred_t;

        typedef typename
            boost::result_of<
                op_make_successors(Range&, filter<pred_t>)
            >::type
        result_type;

        result_type operator()(Range& rng, BinaryPred& pred) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return make_successors(rng, filter<pred_t>(pred));
        }
    };


} // namespace adjacent_filtered_detail


PSTADE_FUNCTION(make_adjacent_filtered, (adjacent_filtered_detail::baby<_, _>))
PSTADE_PIPABLE(adjacent_filtered, (op_make_adjacent_filtered))


} } // namespace pstade::oven


#endif
