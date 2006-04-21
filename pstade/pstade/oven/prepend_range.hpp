#ifndef PSTADE_OVEN_PREPEND_RANGE_HPP
#define PSTADE_OVEN_PREPEND_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/ref.hpp>
#include <boost/utility/base_from_member.hpp>
#include <pstade/egg/function.hpp>
#include "./is_lightweight_proxy.hpp"
#include "./joint_range.hpp"
#include "./range_adaptor.hpp"
#include "./single_range.hpp"


namespace pstade { namespace oven {


template< class Range, class T >
struct prepend_range :
    private boost::base_from_member< single_range<T> >,
    joint_range< single_range<T>, Range >
{
private:
    typedef boost::base_from_member< single_range<T> > single_range_bt;
    typedef joint_range< single_range<T>, Range > super_t;

public:
    explicit prepend_range(Range& rng, T& x) :
        single_range_bt(boost::ref(x)),
        super_t(single_range_bt::member, rng)
    { }
};


namespace prepend_range_detail {


    struct baby_generator
    {
        template< class Range, class T >
        struct apply
        {
            typedef const prepend_range<Range, T> type;
        };

        template< class Result, class Range, class T >
        Result call(Range& rng, T& x)
        {
            return Result(rng, x);
        }
    };


} // namespace prepend_range_detail


PSTADE_EGG_FUNCTION(make_prepend_range, prepend_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(prepended, prepend_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::prepend_range, 2)


#endif
