#ifndef PSTADE_OVEN_ANY_RANGE_HPP
#define PSTADE_OVEN_ANY_RANGE_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_categories.hpp>
#include <pstade/disable_if_copy.hpp>
#include <pstade/egg/generator.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/implicitly_defined.hpp>
#include <pstade/pod_constant.hpp>
#include "./any_iterator.hpp"
#include "./any_range_fwd.hpp"
#include "./iter_range.hpp"
#include "./lightweight_copyable.hpp"
#include "./range_difference.hpp"
#include "./range_reference.hpp"
#include "./range_traversal.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace any_range_detail {


    template< class Reference, class Traversal, class Value, class Difference >
    struct super_
    {
        typedef
            iter_range<
                any_iterator<Reference, Traversal, Value, Difference>,
                // Only SinglePass is considered as "lightweight".
                lightweight_copyable< any_range<Reference, boost::single_pass_traversal_tag, Value, Difference> >
            >
        type;
    };


} // namespace any_range_detail


template< class Reference, class Traversal, class Value, class Difference >
struct any_range :
    any_range_detail::super_<Reference, Traversal, Value, Difference>::type
{
private:
    typedef any_range self_t;
    typedef typename any_range_detail::super_<Reference, Traversal, Value, Difference>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
// structors
    any_range()
    { }

    template< class R, class T, class V, class D >
    any_range(any_range<R, T, V, D> const& other,
        typename enable_if< is_convertible_to_any_iterator<typename any_range<R, T, V, D>::iterator, iter_t> >::type = 0
    ) :
        super_t(boost::begin(other), boost::end(other))
    { }

    template< class It, class Ij >
    any_range(iter_range<It, Ij> const& rng,
        typename enable_if< is_convertible_to_any_iterator<It, iter_t> >::type = 0
    ) :
        super_t(boost::begin(rng), boost::end(rng))
    { }

    template< class Range >
    explicit any_range(Range& rng, typename disable_if_copy<self_t, Range>::type = 0) :
        super_t(boost::begin(rng), boost::end(rng))
    { }

    template< class Range >
    explicit any_range(Range const& rng) :
        super_t(boost::begin(rng), boost::end(rng))
    { }

// assignments: I want to deprecate these.
    template< class Range >
    typename disable_if_copy_assign<self_t, Range>::type operator=(Range& rng)
    {
        super_t::operator=(rng);
        return *this;
    }

    template< class Range >
    self_t& operator=(Range const& rng)
    {
        super_t::operator=(rng);
        return *this;
    }

    PSTADE_IMPLICITLY_DEFINED_COPY_TO_BASE(any_range, super_t)
};


template< class Range >
struct any_range_of
{
    typedef
        any_range<
            typename range_reference<Range>::type,
            typename range_pure_traversal<Range>::type, // should be "pure"; that's type-erasure!
            typename range_value<Range>::type,
            typename range_difference<Range>::type
        >
    type;
};


typedef
    egg::generator<
        any_range<
            range_reference<boost::mpl::_1>,
            range_pure_traversal<boost::mpl::_1>,
            range_value<boost::mpl::_1>,
            range_difference<boost::mpl::_1>
        > const
    >::type
op_make_any_range;

PSTADE_POD_CONSTANT((op_make_any_range), make_any_range) = PSTADE_EGG_GENERATOR;


} } // namespace pstade::oven


#endif
