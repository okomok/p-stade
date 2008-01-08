#ifndef PSTADE_OVEN_BEGIN_END_HPP
#define PSTADE_OVEN_BEGIN_END_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/egg/ambi.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pod_constant.hpp>
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace begin_end_detail {


    struct little_begin
    {
        template< class Myself, class Range >
        struct apply :
            range_iterator<Range>
        { };

        template< class Result, class Range >
        Result call(Range& rng) const
        {
            return boost::begin(rng);
        }
    };

    typedef egg::function<little_begin> base_begin;


    struct little_end
    {
        template< class Myself, class Range >
        struct apply :
            range_iterator<Range>
        { };

        template< class Result, class Range >
        Result call(Range& rng) const
        {
            return boost::end(rng);
        }
    };

    typedef egg::function<little_end> base_end;


} // namespace begin_end_detail


PSTADE_ADL_BARRIER(begin_end) { // for 'boost'

    typedef egg::result_of_ambi0<begin_end_detail::base_begin>::type T_begin;
    PSTADE_POD_CONSTANT((T_begin), begin) = PSTADE_EGG_AMBI({{}});

    typedef egg::result_of_ambi0<begin_end_detail::base_end>::type T_end;
    PSTADE_POD_CONSTANT((T_end), end) = PSTADE_EGG_AMBI({{}});

}


} } // namespace pstade::oven


#endif
