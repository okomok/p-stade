#ifndef PSTADE_OVEN_SUCCESSORS_HPP
#define PSTADE_OVEN_SUCCESSORS_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/pass_by.hpp>
#include "./concepts.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./detail/succeed_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace successors_detail {


    template< class Range, class BinaryFun >
    struct base
    {
        typedef
            detail::succeed_iterator<
                typename range_iterator<Range>::type,
                typename pass_by_value<BinaryFun>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng, BinaryFun& elect) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return aux(boost::begin(rng), boost::end(rng), elect);
        }

        template< class Iterator >
        result_type aux(Iterator first, Iterator last, BinaryFun& elect) const
        {
            return result_type(iter_t(first, elect, last), iter_t(last, elect, last));
        }
    };


} // namespace successors_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(successors, (successors_detail::base<_, _>))


} } // namespace pstade::oven


#endif

