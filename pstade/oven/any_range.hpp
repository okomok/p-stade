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
#include <boost/none.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/disable_if_copy.hpp>
#include <pstade/egg/generator.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/implicitly_defined.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/radish/reset_assignment.hpp>
#include <pstade/radish/swap_reset.hpp>
#include <pstade/radish/swappable.hpp>
#include "./any_fwd.hpp"
#include "./any_iterator.hpp"
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
            iter_range<any_iterator<Reference, Traversal, Value, Difference>,
                radish::swappable   < any_range<Reference, Traversal, Value, Difference>,
                // Only SinglePass is considered as "lightweight".
                lightweight_copyable< any_range<Reference, boost::single_pass_traversal_tag, Value, Difference> > >
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
// structors (This order matters in buggy msvc-7.1.)
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

    any_range(boost::none_t = boost::none)
    { }

    template< class Range >
    explicit any_range(Range& rng, typename disable_if_copy<self_t, Range>::type = 0) :
        super_t(boost::begin(rng), boost::end(rng))
    { }

    template< class Range >
    explicit any_range(Range const& rng) :
        super_t(boost::begin(rng), boost::end(rng))
    { }

    any_range(T_as_type_erasure, self_t const& rng) :
        super_t(iter_t(as_type_erasure, boost::begin(rng)), iter_t(as_type_erasure, boost::end(rng)))
    { }

// assignments
    typedef any_range pstade_radish_this_type;
    #include PSTADE_RADISH_SWAP_RESET()
    #include PSTADE_RADISH_RESET_ASSIGNMENT()

// swappable
    void swap(self_t& other)
    {
        super_t::swap(other);
    }

// boost::any compatibles
    bool iter_empty() const
    {
        return this->begin().empty();
    }

    std::type_info const& iter_type() const
    {
        return this->begin().type();
    }

// workaround
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
T_make_any_range;

PSTADE_POD_CONSTANT((T_make_any_range), make_any_range) = PSTADE_EGG_GENERATOR;


} } // namespace pstade::oven


#endif
