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


#include <pstade/unused_to_copy.hpp>
#include "./iter_range.hpp"
#include "./range_constant_iterator.hpp"
#include "./range_constantable.hpp"
#include "./range_iterator.hpp"


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
private:
    typedef typename sub_range_detail::super_<Range>::type super_t;

public:
    typedef sub_range type;
    typedef typename range_constant_iterator<Range>::type const_iterator; // constantable

// structors
    template< class Range_ >
    sub_range(Range_& rng,
        typename unused_to_copy<type, Range>::type = 0
    ) :
        super_t(rng)
    { }

    template< class Range_ >
    sub_range(Range_ const& rng,
        typename unused_to_copy<type, Range>::type = 0
    ) :
        super_t(rng)
    { }

// copy-assignments
    template< class Range_ >
    typename unused_to_copy_assign<type, Range_>::type
    operator=(Range_& rng)
    {
        super_t::operator=(rng);
        return *this;
    }

    template< class Range_ >
    typename unused_to_copy_assign<type, Range_>::type
    operator=(Range_ const& rng)
    {
        super_t::operator=(rng);
        return *this;
    }
};


} } // namespace pstade::oven


#endif
