#ifndef PSTADE_OVEN_SUB_RANGE_HPP
#define PSTADE_OVEN_SUB_RANGE_HPP


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


#include <pstade/implicitly_defined.hpp>
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
    explicit sub_range()
    { }

    /*implicit*/ sub_range(Range& rng) :
        base(rng)
    { }

    /*implicit*/ sub_range(base const& rng) :
        base(rng)
    { }

    template< class Range_ >
    explicit sub_range(Range_& rng, typename unused_to_copy<type, Range>::type = 0) :
        base(rng)
    { }

    template< class Range_ >
    explicit sub_range(Range_ const& rng) :
        base(rng)
    { }

    template< class Iterator >
    explicit sub_range(Iterator const& first, Iterator const& last) :
        base(first, last)
    { }

// copy-assignments
    template< class Range_ >
    typename unused_to_copy_assign<type, Range_>::type operator=(Range_& rng)
    {
        base::operator=(rng);
        return *this;
    }

    template< class Range_ >
    type& operator=(Range_ const& rng)
    {
        base::operator=(rng);
        return *this;
    }

    // VC8's broken implicitly-defined copy-constructor wrongly
    // calls template constructor of 'iter_range'. Then,
    // sub_range<string> const rng1(str);
    // sub_range<string> rng2(rng1);
    // doesn't compile. So define it from scratch using this macro.
    PSTADE_IMPLICITLY_DEFINED_COPY_TO_BASE(sub_range, base)
};


} } // namespace pstade::oven


#endif
