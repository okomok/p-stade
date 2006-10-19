#ifndef PSTADE_OVEN_ANY_RANGE_HPP
#define PSTADE_OVEN_ANY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // ptrdiff_t
#include <boost/range/iterator_range.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include "./any_iterator.hpp"
#include "./as_lightweight_proxy.hpp"


namespace pstade { namespace oven {


namespace any_range_detail {


    template<
        class Value,
        class Traversal,
        class Reference,
        class Difference
    >
    struct super_
    {
        typedef boost::iterator_range<
            any_iterator<Value, Traversal, Reference, Difference>
        > type;
    };


    // give way to implicitly-declared copy-constructor.
    template< class X, class Y >
    struct never_used_to_copy :
        boost::disable_if< boost::is_same<X, Y>, void * >
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
    typedef typename any_range_detail::super_<Value, Traversal, Reference, Difference>::type super_t;

public:
    template< class Range >
    any_range(Range& rng,
        typename any_range_detail::never_used_to_copy<any_range, Range>::type = 0
    ) :
        super_t(rng)
    { }

    template< class Range >
    any_range(Range const& rng) :
        super_t(rng)
    { }
};


} } // namespace pstade::oven


#endif
