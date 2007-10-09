#ifndef PSTADE_OVEN_ANY_INDEX_RANGE_HPP
#define PSTADE_OVEN_ANY_INDEX_RANGE_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <typeinfo>
#include <boost/none.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/disable_if_copy.hpp>
#include <pstade/egg/generator.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/implicitly_defined.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/radish/swappable.hpp>
#include <pstade/reset_assignment.hpp>
#include "./any_index_iterator.hpp"
#include "./any_range_fwd.hpp"
#include "./iter_range.hpp"
#include "./lightweight_copyable.hpp"
#include "./range_difference.hpp"
#include "./range_reference.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace any_index_range_detail {


    template< class Reference, class Value, class Difference >
    struct super_
    {
        typedef
            iter_range<
                any_index_iterator<Reference, Value, Difference>,
                radish::swappable    < any_index_range<Reference, Value, Difference>,
                lightweight_copyable < any_index_range<Reference, Value, Difference> > >
            >
        type;
    };


    template< class Super, class Iterator > inline
    Super make(Iterator first, Iterator last)
    {
        typedef typename Super::iterator iter_t;
        return Super(iter_t(0, first), iter_t(last - first, first));
    }


} // namespace any_index_range_detail


template< class Reference, class Value, class Difference >
struct any_index_range :
    any_index_range_detail::super_<Reference, Value, Difference>::type
{
private:
    typedef any_index_range self_t;
    typedef typename any_index_range_detail::super_<Reference, Value, Difference>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    typedef typename iter_t::index_type index_type;

// structors
    any_index_range(boost::none_t = boost::none)
    { }

    template< class R, class V, class D >
    any_index_range(any_index_range<R, V, D> const& other,
        typename enable_if< is_convertible_to_any_index_iterator<typename any_index_range<R, V, D>::iterator, iter_t> >::type = 0
    ) :
        super_t(any_index_range_detail::make<super_t>(boost::begin(other), boost::end(other)))
    { }

    template< class It, class Ij >
    any_index_range(iter_range<It, Ij> const& rng,
        typename enable_if< is_convertible_to_any_index_iterator<It, iter_t> >::type = 0
    ) :
        super_t(any_index_range_detail::make<super_t>(boost::begin(rng), boost::end(rng)))
    { }

    template< class Range >
    explicit any_index_range(Range& rng, typename disable_if_copy<self_t, Range>::type = 0) :
        super_t(any_index_range_detail::make<super_t>(boost::begin(rng), boost::end(rng)))
    { }

    template< class Range >
    explicit any_index_range(Range const& rng) :
        super_t(any_index_range_detail::make<super_t>(boost::begin(rng), boost::end(rng)))
    { }

// assignments
    template< class Range >
    void reset(Range& rng)
    {
        self_t(rng).swap(*this);
    }

    template< class Range >
    void reset(Range const& rng)
    {
        self_t(rng).swap(*this);
    }

    void reset(boost::none_t = boost::none)
    {
        self_t().swap(*this);
    }

    PSTADE_RESET_ASSIGNMENT(any_index_range)

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
    PSTADE_IMPLICITLY_DEFINED_COPY_TO_BASE(any_index_range, super_t)
};


template< class Range >
struct any_index_range_of
{
    typedef
        any_index_range<
            typename range_reference<Range>::type,
            typename range_value<Range>::type,
            typename range_difference<Range>::type
        >
    type;
};


typedef
    egg::generator<
        any_index_range<
            range_reference<boost::mpl::_1>,
            range_value<boost::mpl::_1>,
            range_difference<boost::mpl::_1>
        > const
    >::type
T_make_any_index_range;

PSTADE_POD_CONSTANT((T_make_any_index_range), make_any_index_range) = PSTADE_EGG_GENERATOR;


} } // namespace pstade::oven


#endif
