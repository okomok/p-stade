#ifndef PSTADE_OVEN_DELIMITED_HPP
#define PSTADE_OVEN_DELIMITED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/prelude.hpp"
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concatenated.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./jointed.hpp"
#include "./transformed.hpp"


namespace pstade { namespace oven {


namespace delimited_detail {


    template< class DelimiterRange >
    struct join :
        callable< join<DelimiterRange> >
    {
        // Hold the base range by value for copying to outer scope.
        typedef typename
            iter_range_of<DelimiterRange>::type
        delim_t;

        template< class Myself, class LocalRange >
        struct apply :
            boost::result_of<
                op_make_jointed(delim_t const&, LocalRange&)
            >
        { };

        template< class Result, class LocalRange >
        Result call(LocalRange& local) const
        {
            return make_jointed(m_delim, local);
        }

        explicit join()
        { }

        explicit join(DelimiterRange& delim) :
            m_delim(delim)
        { }

    private:
        delim_t m_delim;
    };


    template< class SegmentRange, class DelimiterRange >
    struct baby
    {
        typedef
            typename boost::result_of<
                op_make_concatenated(
                    typename boost::result_of<
                        op_make_transformed<>(SegmentRange&, join<DelimiterRange>)
                    >::type
                )
            >::type
        result_type;

        result_type operator()(SegmentRange& rngs, DelimiterRange& delim) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<SegmentRange>));
            PSTADE_CONCEPT_ASSERT((SinglePass<DelimiterRange>));

            return make_concatenated(
                make_transformed(rngs, join<DelimiterRange>(delim))
            );
        }
    };


} // namespace delimited_detail


PSTADE_FUNCTION(make_delimited, (delimited_detail::baby<_, _>))
PSTADE_PIPABLE(delimited, (op_make_delimited))


} } // namespace pstade::oven


#endif
