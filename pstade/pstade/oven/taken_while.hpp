#ifndef PSTADE_OVEN_TAKEN_WHILE_HPP
#define PSTADE_OVEN_TAKEN_WHILE_HPP
#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./detail/take_while_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./read.hpp"


namespace pstade { namespace oven {


namespace taken_while_detail {


    template< class Predicate >
    struct read_then
    {
        template< class Iterator >
        bool operator()(Iterator it)
        {
            return m_pred(read(it));
        }

        explicit read_then()
        { }

        explicit read_then(Predicate pred) :
            m_pred(pred)
        { }

    private:
        Predicate m_pred;
    };


    template< class Range, class Predicate >
    struct baby
    {
        typedef
            read_then<typename pass_by_value<Predicate>::type>
        read_then_pred_t;

        typedef
            detail::take_while_iterator<
                typename range_iterator<Range>::type,
                read_then_pred_t
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng, Predicate& pred) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

            return result_type(
                iter_t(boost::begin(rng), boost::end(rng), read_then_pred_t(pred)),
                iter_t(boost::end(rng),   boost::end(rng), read_then_pred_t(pred))
            );
        }
    };


} // namespace taken_while_detail


PSTADE_FUNCTION(make_taken_while, (taken_while_detail::baby<_, _>))
PSTADE_PIPABLE(taken_while, (op_make_taken_while))


} } // namespace pstade::oven


#endif
