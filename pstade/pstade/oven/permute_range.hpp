#ifndef PSTADE_OVEN_PERMUTE_RANGE_HPP
#define PSTADE_OVEN_PERMUTE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./permute_iterator.hpp"


namespace pstade { namespace oven {


namespace permute_range_detail {


    template< class ElementRange, class IndexRange >
    struct super_ :
        iter_range<
            permute_iterator<
                typename range_iterator<ElementRange>::type,
                typename range_iterator<IndexRange>::type
            >
        >
    { };


} // namespace permute_range_detail


template< class ElementRange, class IndexRange >
struct permute_range :
    permute_range_detail::super_<ElementRange, IndexRange>::type,
    private as_lightweight_proxy< permute_range<ElementRange, IndexRange> >
{
    PSTADE_CONCEPT_ASSERT((RandomAccess<ElementRange>));
    PSTADE_CONCEPT_ASSERT((SinglePass<IndexRange>));
    // PSTADE_CONCEPT_ASSERT((Readable<IndexRange>));
    typedef IndexRange index_range_type;

private:
    typedef typename permute_range_detail::super_<ElementRange, IndexRange>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    permute_range(ElementRange& erng, IndexRange& irng) :
        super_t(
            iter_t(boost::begin(erng), boost::begin(irng)),
            iter_t(boost::begin(erng), boost::end(irng)) // never pass 'boost::end(erng)'.
        )
    { }

    typedef ElementRange pstade_oven_range_base_type;
};


PSTADE_OBJECT_GENERATOR(make_permute_range, const permute_range, (by_qualified)(by_qualified))
PSTADE_PIPABLE(permuted, op_make_permute_range)


} } // namespace pstade::oven


#endif
