#ifndef PSTADE_OVEN_POPPED_HPP
#define PSTADE_OVEN_POPPED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This never accepts an empty range,
// following Container and Haskell's 'init'.


#include <boost/assert.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./detail/begin_end_tag.hpp"
#include "./detail/pop_iterator_of_forward.hpp"
#include "./detail/pop_iterator_of_single_pass.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./range_traversal.hpp"


namespace pstade { namespace oven {


namespace popped_detail {


    template< class Range >
    struct baby
    {
        typedef typename
            range_iterator<Range>::type
        base_iter_t;

        typedef typename
            range_traversal<Range>::type
        base_trv_t;

        typedef typename
            boost::mpl::eval_if< is_convertible<base_trv_t, boost::bidirectional_traversal_tag>,
                iter_range_of<Range>,
                boost::mpl::eval_if< is_convertible<base_trv_t, boost::forward_traversal_tag>,
                    iter_range< detail::pop_iterator_of_forward<base_iter_t> >,
                    iter_range< detail::pop_iterator_of_single_pass<base_iter_t> >
                >
            >::type const
        result_type;

        result_type operator()(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            BOOST_ASSERT(!boost::empty(rng));
            return aux(boost::begin(rng), boost::end(rng), typename range_traversal<Range>::type());
        }

        template< class Iterator >
        result_type aux(Iterator first, Iterator last, boost::bidirectional_traversal_tag) const
        {
            PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
            return result_type(first, boost::prior(last));
        }

        template< class Iterator >
        result_type aux(Iterator first, Iterator last, boost::forward_traversal_tag) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            typedef typename result_type::iterator iter_t;
            return result_type(iter_t(first, last), iter_t(last));
        }

        template< class Iterator >
        result_type aux(Iterator first, Iterator last, boost::single_pass_traversal_tag) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            typedef typename result_type::iterator iter_t;
            return result_type(iter_t(first, detail::begin_tag()), iter_t(last, detail::end_tag()));
        }
    };


} // namespace popped_detail


PSTADE_FUNCTION(make_popped, (popped_detail::baby<_>))
PSTADE_PIPABLE(popped, (op_make_popped))


} } // namespace pstade::oven


#endif
