#ifndef PSTADE_OVEN_CHECKED_HPP
#define PSTADE_OVEN_CHECKED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/egg/ambi.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pod_constant.hpp>
#include "./concepts.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./detail/check_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


// checked
//

namespace checked_detail {


    template< class Range >
    struct base
    {
        typedef
            detail::check_iterator<
                typename range_iterator<Range>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            return aux(boost::begin(rng), boost::end(rng));
        }

        template< class Iterator >
        result_type aux(Iterator first, Iterator last) const
        {
            return result_type(iter_t(first, first, last), iter_t(last, first, last));
        }
    };


} // namespace checked_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(checked, (checked_detail::base<_>))


// checked_begin
//

namespace checked_begin_detail {


    struct little
    {
        template< class Myself, class Range >
        struct apply
        {
            typedef
                detail::check_iterator<
                    typename range_iterator<Range>::type
                >
            type;
        };

        template< class Result, class Range >
        Result call(Range& rng) const
        {
            return make_checked(rng).begin();
        }
    };

    typedef egg::function<little> base;


} // namespace checked_begin_detail


typedef egg::result_of_ambi0<checked_begin_detail::base>::type T_checked_begin;
PSTADE_POD_CONSTANT((T_checked_begin), checked_begin) = PSTADE_EGG_AMBI({{}});


} } // namespace pstade::oven


#if !defined(NDEBUG)
    #define PSTADE_OVEN_CHECKED(Rng) pstade::oven::make_checked(Rng)
    #define PSTADE_OVEN_CHECKED_BEGIN(Rng) pstade::oven::checked_begin(Rng)
#else
    #define PSTADE_OVEN_CHECKED(Rng) Rng
    #define PSTADE_OVEN_CHECKED_BEGIN(Rng) boost::begin(Rng)
#endif


#if defined(PSTADE_OVEN_IN_BOOST)
    #define BOOST_OVEN_CHECKED PSTADE_OVEN_CHECKED
    #define BOOST_OVEN_CHECKED_BEGIN PSTADE_OVEN_CHECKED_BEGIN
#endif


#endif
