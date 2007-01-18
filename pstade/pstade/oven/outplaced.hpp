#ifndef PSTADE_OVEN_OUTPLACED_HPP
#define PSTADE_OVEN_OUTPLACED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Rejected...
//
// See "./sort_range.hpp"


// Note:
//
// Iterators manage temporary container for BOOST_FOREACH.


#include <memory> // auto_ptr
#include <vector>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include <pstade/unused.hpp>
#include "./copy_range.hpp"
#include "./concepts.hpp"
#include "./directed.hpp"
#include "./indirected.hpp"
#include "./range_iterator.hpp"
#include "./shared.hpp"


namespace pstade { namespace oven {


struct op_make_outplaced :
    callable<op_make_outplaced>
{
    template< class Range >
    struct iter_sequence
    {   
        typedef typename range_iterator<Range>::type iter_t;
        typedef std::vector<iter_t> type;
    };

    template< class Myself, class Range, class UnaryFun = op_unused >
    struct apply :
        boost::result_of<
            op_make_indirected<>(
                typename boost::result_of<
                    op_make_shared(typename iter_sequence<Range>::type *)
                >::type
            )
        >
    { };

    template< class Result, class Range, class UnaryFun >
    Result call(Range& rng, UnaryFun& fun) const
    {
        PSTADE_CONCEPT_ASSERT((Forward<Range>));

        typedef typename iter_sequence<Range>::type iter_seq_t;

        // 'shared' range size never be affected by its holding sequence
        // once constructed. So, first of all, you must initialize the sequence
        // before passing it to 'make_shared'.
        std::auto_ptr<iter_seq_t> pseq(new iter_seq_t());
        *pseq = oven::copy_range<iter_seq_t>(rng|directed);

        // Question:
        // What should be passed to 'fun'?
        fun(*pseq);

        return make_indirected(make_shared(pseq.release()));
    }

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return (*this)(rng, unused);
    }
};


PSTADE_CONSTANT(make_outplaced, (op_make_outplaced))
PSTADE_PIPABLE(outplaced, (op_make_outplaced))


} } // namespace pstade::oven


#endif
