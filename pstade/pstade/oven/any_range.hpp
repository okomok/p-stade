#ifndef PSTADE_OVEN_ANY_RANGE_HPP
#define PSTADE_OVEN_ANY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // ptrdiff_t
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include <pstade/unused_to_copy.hpp>
#include "./any_iterator.hpp"
#include "./as_lightweight_proxy.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace any_range_detail {


    template<
        class Value,
        class Traversal,
        class Reference,
        class Difference
    >
    struct super_ :
        iter_range<
            any_iterator<Value, Traversal, Reference, Difference>
        >
    { };


} // namespace any_range_detail


template<
    class Value,
    class Traversal,
    class Reference  = Value&,
    class Difference = std::ptrdiff_t
>
struct any_range :
    any_range_detail::super_<Value, Traversal, Reference, Difference>::type,
    private as_lightweight_proxy< any_range<Value, Traversal, Reference, Difference> >
{
private:
    typedef any_range selt_t;
    typedef typename any_range_detail::super_<Value, Traversal, Reference, Difference>::type super_t;

public:
// structors
    template< class Range >
    any_range(Range& rng, typename unused_to_copy<selt_t, Range>::type = 0) :
        super_t(boost::begin(rng), boost::end(rng))
    { }

    template< class Range >
    any_range(Range const& rng) :
        super_t(boost::begin(rng), boost::end(rng))
    { }

// copy-assignments
    template< class Range_ >
    typename unused_to_copy_assign<selt_t, Range_>::type operator=(Range_& rng)
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
