#ifndef PSTADE_OVEN_SUB_RANGE_HPP
#define PSTADE_OVEN_SUB_RANGE_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// The template-constructor is now explicit,
// which seems politically correct and enables 'to_base_range'.


#include <pstade/disable_if_copy.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/implicitly_defined.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/radish/reset_assignment.hpp>
#include "./iter_range.hpp"
#include "./lightweight_copyable.hpp"
#include "./range_constant_iterator.hpp"
#include "./range_constantable.hpp"


namespace pstade { namespace oven {


template< class Range >
struct sub_range;


namespace sub_range_detail {


    template< class Range >
    struct super_ :
        iter_range_of<Range,
            radish::swappable   < sub_range<Range>,
            range_constantable  < sub_range<Range>, typename range_constant_iterator<Range>::type,
            lightweight_copyable< sub_range<Range> > > >
        >
    { };


} // namespace sub_range_detail


template< class Range >
struct sub_range :
    sub_range_detail::super_<Range>::type
{
private:
    typedef sub_range self_t;
    typedef typename sub_range_detail::super_<Range>::type super_t;

public:
    typedef self_t type;
    typedef super_t base;
    typedef typename range_constant_iterator<Range>::type const_iterator;

public:
// structors
    sub_range()
    { }

    sub_range(Range& rng) :
        super_t(rng)
    { }

    template< class It, class Ij >
    sub_range(iter_range<It, Ij> const& rng,
        typename enable_if< is_convertible<iter_range<It, Ij>, super_t> >::type = 0
    ) :
        super_t(rng)
    { }

    template< class Iterator >
    sub_range(Iterator first, Iterator last) :
        super_t(first, last)
    { }

    template< class Range_ >
    explicit sub_range(Range_& rng, typename disable_if_copy<self_t, Range_>::type = 0) :
        super_t(rng)
    { }

    template< class Range_ >
    explicit sub_range(Range_ const& rng) :
        super_t(rng)
    { }

// assignments
    typedef sub_range pstade_radish_this_type;
    #include PSTADE_RADISH_RESET_ASSIGNMENT()

// swappable
    void swap(self_t& other)
    {
        super_t::swap(other);
    }

// workaround
    PSTADE_IMPLICITLY_DEFINED_COPY_TO_BASE(sub_range, super_t)
};


} } // namespace pstade::oven


#endif
