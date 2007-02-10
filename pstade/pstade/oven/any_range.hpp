#ifndef PSTADE_OVEN_ANY_RANGE_HPP
#define PSTADE_OVEN_ANY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_categories.hpp>
#include <pstade/unused_to_copy.hpp>
#include "./any_iterator.hpp"
#include "./as_lightweight_proxy.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace any_range_detail {


    template<
        class Reference,
        class Traversal,
        class Value,
        class Difference
    >
    struct super_
    {
        typedef
            iter_range<
                any_iterator<Reference, Traversal, Value, Difference>
            >
        type;
    };


} // namespace any_range_detail


template<
    class Reference,
    class Traversal  = boost::single_pass_traversal_tag,
    class Value      = boost::use_default,
    class Difference = boost::use_default
>
struct any_range :
    any_range_detail::super_<Reference, Traversal, Value, Difference>::type,
    private as_lightweight_proxy< any_range<Reference, Traversal, Value, Difference> >
{
private:
    typedef any_range self_t;
    typedef typename any_range_detail::super_<Reference, Traversal, Value, Difference>::type super_t;

public:
// structors
    any_range()
    { }

    template< class Range >
    /*implicit*/ any_range(Range& rng, typename unused_to_copy<self_t, Range>::type = 0) :
        super_t(boost::begin(rng), boost::end(rng))
    { }

    template< class Range >
    /*implicit*/ any_range(Range const& rng) :
        super_t(boost::begin(rng), boost::end(rng))
    { }

// copy-assignments
    template< class Range_ >
    typename unused_to_copy_assign<self_t, Range_>::type operator=(Range_& rng)
    {
        super_t::operator=(rng);
        return *this;
    }

    template< class Range_ >
    self_t& operator=(Range_ const& rng)
    {
        super_t::operator=(rng);
        return *this;
    }
};


} } // namespace pstade::oven


#endif
