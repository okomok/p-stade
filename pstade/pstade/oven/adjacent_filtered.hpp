#ifndef PSTADE_OVEN_ADJACENT_FILTERERD_HPP
#define PSTADE_OVEN_ADJACENT_FILTERERD_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/result_of.hpp>
#include <pstade/as.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./successors.hpp"


namespace pstade { namespace oven {


namespace adjacent_filtered_detail {


    template< class BinaryPred >
    struct filter
    {
        template< class ForwardIter >
        ForwardIter operator()(ForwardIter const& first, ForwardIter const& last) const
        {
            ForwardIter next(first);
            while (++next != last) {
                if (m_pred(as_ref(*first), as_ref(*next)))
                    return next;
            }

            return last;
        }

        explicit filter()
        { }

        explicit filter(BinaryPred const& pred) :
            m_pred(pred)
        { }

    private:
        BinaryPred m_pred;
    };


    template< class Range, class BinaryPred >
    struct baby
    {
        typedef
            filter<
                typename pass_by_value<BinaryPred>::type
            >
        finder_t;

        typedef typename
            boost::result_of<
                op_make_successors(Range&, finder_t)
            >::type
        result;

        result call(Range& rng, BinaryPred& pred)
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            return make_successors(rng, finder_t(pred));
        }
    };


} // namespace adjacent_filtered_detail


PSTADE_FUNCTION(make_adjacent_filtered, (adjacent_filtered_detail::baby<_, _>))
PSTADE_PIPABLE(adjacent_filtered, (op_make_adjacent_filtered))


} } // namespace pstade::oven


#endif
