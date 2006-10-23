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
// "sub_range" which conforms to Assignalbe and CopyConstructible,
// but not DefaultConstructible.


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <pstade/unused_to_copy.hpp>
#include "./iter_range.hpp"
#include "./range_constant_iterator.hpp"
#include "./range_constantable.hpp"
#include "./range_iterator.hpp"


#if BOOST_WORKAROUND(BOOST_MSVC, == 1400)
    // 12.8/8 says "the copy constructor for *the class* is used".
    // But VC8 passes the 'sub_range' object to 'iter_range' constructor as is.
    // Then the template constructor of 'iter_range' is chosen,
    // and 'boost::begin' is called. Thus, const-ness is propagated.
    // At last, 'sub_range' becomes noncopyable from 'const sub_range'.
    #define PSTADE_OVEN_IMPLICITLY_DEFINED_COPY_IS_BROKEN
#endif


namespace pstade { namespace oven {


template< class Range >
struct sub_range;


namespace sub_range_detail {


    template< class Range >
    struct super_
    {
        typedef
            iter_range< typename range_iterator<Range>::type >
        type;
    };


} // namespace sub_range_detail


template< class Range >
struct sub_range :
    sub_range_detail::super_<Range>::type,
    private range_constantable<sub_range<Range>, typename range_iterator_const<Range>::type>
{
    typedef sub_range<Range> type;
    typedef typename sub_range_detail::super_<Range>::type super_t;
    typedef typename range_constant_iterator<Range>::type const_iterator; // constantable

// structors
    template< class Range_ >
    sub_range(Range_& rng, typename unused_to_copy<type, Range>::type = 0) :
        super_t(rng)
    { }

    template< class Range_ >
    sub_range(Range_ const& rng) :
        super_t(rng)
    { }

// copy-assignments
    template< class Range_ >
    typename unused_to_copy_assign<type, Range_>::type operator=(Range_& rng)
    {
        super_t::operator=(rng);
        return *this;
    }

    template< class Range_ >
    type& operator=(Range_ const& rng)
    {
        super_t::operator=(rng);
        return *this;
    }

#if defined(PSTADE_OVEN_IMPLICITLY_DEFINED_COPY_IS_BROKEN)
    sub_range(type const& other) :
        super_t(static_cast<super_t const&>(other))
    { }

    type& operator=(type const& other)
    {
        super_t::operator=(static_cast<super_t const&>(other));
        return *this;
    }
#endif
};


} } // namespace pstade::oven


#endif
