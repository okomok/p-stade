#ifndef PSTADE_OVEN_REMOVED_HPP
#define PSTADE_OVEN_REMOVED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Akira Takahashi and heisseswasser 2010.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// What:
//
// filtered(!p)

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/pass_by.hpp>
#include "./concepts.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./detail/filter_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace removed_detail {


    template< class Range, class Predicate >
    struct base
    {
        struct T_not {
            typedef bool result_type;
            T_not(Predicate& pred) : m_pred(pred) {}

            template <class T>
            result_type operator()(T& x) const
            {
                return !m_pred(x);
            }

            Predicate& m_pred;
        };

        typedef T_not not_t;

        typedef
            detail::filter_iterator<
                typename pass_by_value<not_t>::type,
                typename range_iterator<Range>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng, Predicate& pred) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return aux(boost::begin(rng), boost::end(rng), pred);
        }

        template< class Iterator >
        result_type aux(Iterator first, Iterator last, Predicate& pred) const
        {
            return result_type(iter_t(not_t(pred), first, last), iter_t(not_t(pred), last, last));
        }
    };


} // namespace removed_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(removed, (removed_detail::base<_, _>))


} } // namespace pstade::oven


#endif

