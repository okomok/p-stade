#ifndef PSTADE_OVEN_ANY_RANGE_HPP
#define PSTADE_OVEN_ANY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // ptrdiff_t
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./any_iterator.hpp"


namespace pstade { namespace oven {


namespace any_range_detail {


    template<
        class Reference,
        class Traversal,
        class Difference = std::ptrdiff_t
    >
    struct super_
    {
        typedef boost::iterator_range<
            any_iterator<Reference, Traversal, Difference>
        > type;
    };


} // namespace any_range_detail


template<
    class Reference,
    class Traversal,
    class Difference = std::ptrdiff_t
>
struct any_range :
    any_range_detail::super_<Reference, Traversal, Difference>::type,
    private as_lightweight_proxy< any_range<Reference, Traversal, Difference> >
{
private:
    typedef typename any_range_detail::super_<Reference, Traversal, Difference>::type super_t;

public:
    template< class Range >
    explicit any_range(Range& rng,
        typename boost::disable_if< boost::is_same<Range, any_range> >::type * = 0
    ) :
        super_t(boost::begin(rng), boost::end(rng))
    { }

    template< class Range >
    explicit any_range(Range const& rng) :
        super_t(boost::begin(rng), boost::end(rng))
    { }
};


} } // namespace pstade::oven


#endif
