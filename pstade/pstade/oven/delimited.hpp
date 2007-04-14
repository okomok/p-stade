#ifndef PSTADE_OVEN_DELIMITED_HPP
#define PSTADE_OVEN_DELIMITED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concatenated.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp" // iter_range_of
#include "./jointed.hpp"
#include "./transformed.hpp"


namespace pstade { namespace oven {


namespace delimited_detail {


    template< class Delimiter >
    struct with :
        callable< with<Delimiter> >
    {
        // Hold the base range by value.
        typedef typename
            iter_range_of<Delimiter>::type
        delim_t;

        template< class Myself, class LocalRange >
        struct apply :
            boost::result_of<
                op_make_jointed(delim_t&, LocalRange&)
            >
        { };

        template< class Result, class LocalRange >
        Result call(LocalRange& local) const
        {
            return make_jointed(m_delim, local);
        }

        explicit with()
        { }

        explicit with(Delimiter& delim) :
            m_delim(delim)
        { }

    private:
        delim_t m_delim;
    };


    template< class SegmentRange, class Delimiter >
    struct baby
    {
        typedef
            typename boost::result_of<
                op_make_concatenated(
                    typename boost::result_of<
                        op_make_transformed<>(SegmentRange&, with<Delimiter>)
                    >::type
                )
            >::type
        result_type;

        result_type operator()(SegmentRange& rngs, Delimiter& delim) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<SegmentRange>));
            PSTADE_CONCEPT_ASSERT((SinglePass<Delimiter>));

            return make_concatenated(
                make_transformed(rngs, with<Delimiter>(delim))
            );
        }
    };


} // namespace delimited_detail


PSTADE_FUNCTION(make_delimited, (delimited_detail::baby<_, _>))
PSTADE_PIPABLE(delimited, (op_make_delimited))


} } // namespace pstade::oven


#endif
