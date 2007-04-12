#ifndef PSTADE_OVEN_TAKEN_HPP
#define PSTADE_OVEN_TAKEN_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This could return RandomAccess, but can't return Bidirectional...


#include <boost/assert.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./range_difference.hpp"
#include "./taken_while.hpp"


namespace pstade { namespace oven {


namespace taken_detail {


    template< class Difference >
    struct count_down
    {
        template< class T >
        bool operator()(T const&)
        {
            return m_n--
                != 0; // suppress a VC++ warning.
        }

        explicit count_down()
        { }

        explicit count_down(Difference n) :
            m_n(n)
        { }

    private:
        Difference m_n;
    };


    template< class Range, class >
    struct baby
    {
        typedef typename
            range_difference<Range>::type
        diff_t;

        typedef typename
            boost::result_of<
                op_make_taken_while(Range&, count_down<diff_t>)
            >::type
        result_type;

        result_type operator()(Range& rng, diff_t n) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            BOOST_ASSERT(0 <= n);

            return make_taken_while(rng, count_down<diff_t>(n));
        }
    };


} // namespace taken_detail


PSTADE_FUNCTION(make_taken, (taken_detail::baby<_, _>))
PSTADE_PIPABLE(taken, (op_make_taken))


} } // namespace pstade::oven


#endif
