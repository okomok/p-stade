#ifndef PSTADE_OVEN_OUTPLACED_HPP
#define PSTADE_OVEN_OUTPLACED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] Gabhan Berry, C++ View Objects, Dr.Dobb's Portal, 2006.
//     http://www.ddj.com/dept/cpp/196513737


#include <vector>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/result_of.hpp>
#include "./concepts.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./outdirected.hpp"
#include "./range_iterator.hpp"
#include "./shared.hpp"


namespace pstade { namespace oven {


namespace outplaced_detail {


    template< class Range >
    struct iter_sequence
    {   
        typedef
            std::vector<
                typename range_iterator<Range>::type
            >
        type;
    };


    template< class Range >
    struct base
    {
        typedef typename
            iter_sequence<Range>::type
        iter_seq_t;

        typedef typename
            result_of<
                T_shared(iter_seq_t *)
            >::type
        result_type;

        result_type operator()(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            typename result_of<T_make_outdirected(Range&)>::type its = make_outdirected(rng);
            return shared( new iter_seq_t(boost::begin(its), boost::end(its)) );
        }
    };


} // namespace outplaced_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(outplaced, (outplaced_detail::base<_>))


} } // namespace pstade::oven


#endif
