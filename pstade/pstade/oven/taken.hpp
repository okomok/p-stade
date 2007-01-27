#ifndef PSTADE_OVEN_TAKEN_HPP
#define PSTADE_OVEN_TAKEN_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/range/begin.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./detail/debug_in_distance.hpp"
#include "./detail/next_prior.hpp" // next
#include "./range_difference.hpp"
#include "./range_traversal.hpp"
#include "./sub_range_result.hpp"
#include "./taken_while.hpp"


namespace pstade { namespace oven {


namespace taken_detail {


    template< class Difference >
    struct count_down
    {
        explicit count_down(Difference const& d) :
            m_d(d)
        { }

        // 'take_while_iterator', which is used on single pass,
        // does not require call-operator to be 'const'.
        template< class T >
        bool operator()(T const&)
        {
            return m_d--
                != 0; // suppress a VC++ warning.
        }

    private:
        Difference m_d;
    };


    template< class Result, class Difference, class Range > inline
    Result aux(Range& rng, Difference const& d, boost::forward_traversal_tag)
    {
        PSTADE_CONCEPT_ASSERT((Forward<Range>));
        BOOST_ASSERT(detail::debug_in_distance(d, rng));

        return Result(
            boost::begin(rng),
            detail::next(boost::begin(rng), d)
        );
    }

    template< class Result, class Difference, class Range > inline
    Result aux(Range& rng, Difference const& d, boost::single_pass_traversal_tag)
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
        return make_taken_while(rng, count_down<Difference>(d));
    }


    template< class Range, class >
    struct baby
    {
        typedef typename
            range_difference<Range>::type
        diff_t;

        typedef typename
            boost::mpl::eval_if<
                boost::is_convertible<
                    typename range_traversal<Range>::type,
                    boost::forward_traversal_tag
                >,
                sub_range_result<Range>,
                boost::result_of<op_make_taken_while(Range&, count_down<diff_t>)>
            >::type
        result;

        result call(Range& rng, diff_t const& d)
        {
            return taken_detail::aux<result, diff_t>(
                rng, d, typename range_traversal<Range>::type()
            );
        }
    };


} // namespace taken_detail


PSTADE_FUNCTION(make_taken, (taken_detail::baby<_, _>))
PSTADE_PIPABLE(taken, (op_make_taken))


} } // namespace pstade::oven


#endif
