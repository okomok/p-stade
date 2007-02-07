#ifndef PSTADE_OVEN_PERMUTED_HPP
#define PSTADE_OVEN_PERMUTED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./permute_iterator.hpp"


namespace pstade { namespace oven {


namespace permuted_detail {


    template< class ElementRange, class IndexRange >
    struct baby
    {
        typedef
            permute_iterator<
                typename range_iterator<ElementRange>::type,
                typename range_iterator<IndexRange>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result;

        result call(ElementRange& erng, IndexRange& irng)
        {
            PSTADE_CONCEPT_ASSERT((RandomAccess<ElementRange>));
            PSTADE_CONCEPT_ASSERT((SinglePass<IndexRange>));

            return result(
                iter_t(boost::begin(erng), boost::begin(irng)),
                iter_t(boost::begin(erng), boost::end(irng)) // never pass 'boost::end(erng)'.
            );
        }
    };


} // namespace permuted_detail


PSTADE_FUNCTION(make_permuted, (permuted_detail::baby<_, _>))
PSTADE_PIPABLE(permuted, (op_make_permuted))


} } // namespace pstade::oven


#endif
