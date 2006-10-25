#ifndef PSTADE_OVEN_SUB_RANGE_HPP
#define PSTADE_OVEN_SUB_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/unused_to_copy.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./range_constant_iterator.hpp"
#include "./range_constantable.hpp"
#include "./sub_range_base.hpp"


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, == 1400)
    // 12.8/8 says "the *copy constructor* for the class is used".
    // But VC8's implicitly-defined copy-constructor could call
    // any unary template constructor maybe after overload resolution.
    #define PSTADE_implicitly_defined_copy_is_broken
#endif


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
    sub_range()
    { }

    template< class Range_ >
    sub_range(Range_& rng, typename unused_to_copy<type, Range>::type = 0) :
        base(rng)
    { }

    template< class Range_ >
    sub_range(Range_ const& rng) :
        base(rng)
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

#if defined(PSTADE_implicitly_defined_copy_is_broken)
    sub_range(type const& other) :
        base(static_cast<base const&>(other))
    { }

    type& operator=(type const& other)
    {
        base::operator=(static_cast<base const&>(other));
        return *this;
    }
#endif
};


} } // namespace pstade::oven


#undef PSTADE_implicitly_defined_copy_is_broken


#endif
