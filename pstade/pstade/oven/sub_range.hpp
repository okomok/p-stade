#ifndef PSTADE_OVEN_SUB_RANGE_HPP
#define PSTADE_OVEN_SUB_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// "sub_range" which conforms to Assignable and CopyConstructible,
// but not DefaultConstructible.


#include <pstade/unused_to_copy.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./range_constant_iterator.hpp"
#include "./range_constantable.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


template< class Range >
struct sub_range :
    sub_range_base<Range>::type,
    private range_constantable<sub_range<Range>, typename range_constant_iterator<Range>::type>,
    private as_lightweight_proxy< sub_range<Range> >
{
    typedef sub_range type;
    typedef typename sub_range_base<Range>::type base;
    typedef typename range_constant_iterator<Range>::type const_iterator; // constantable

// structors
    template< class Range_ >
    sub_range(Range_& rng,
        typename unused_to_copy<type, Range>::type = 0
    ) :
        base(rng)
    { }

    template< class Range_ >
    sub_range(Range_ const& rng,
        typename unused_to_copy<type, Range>::type = 0
    ) :
        base(rng)
    { }

// copy-assignments
    template< class Range_ >
    typename unused_to_copy_assign<type, Range_>::type
    operator=(Range_& rng)
    {
        base::operator=(rng);
        return *this;
    }

    template< class Range_ >
    typename unused_to_copy_assign<type, Range_>::type
    operator=(Range_ const& rng)
    {
        base::operator=(rng);
        return *this;
    }
};


} } // namespace pstade::oven


#include <boost/mpl/bool.hpp>

namespace pstade {

    template< class Range >
    struct is_slice_copyable<
        oven::sub_range<Range>,
        typename oven::sub_range_base<Range>::type
    > :
        boost::mpl::true_
    { };

} // namespace pstade


#endif
