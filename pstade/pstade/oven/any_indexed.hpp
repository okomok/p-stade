#ifndef PSTADE_OVEN_ANY_INDEXED_HPP
#define PSTADE_OVEN_ANY_INDEXED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This range was originally written by yotto-k.
// http://d.hatena.ne.jp/yotto-k/20071010


#include <boost/none.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/as_type_erasure.hpp>
#include <pstade/disable_if_copy.hpp>
#include <pstade/egg/generator.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/implicitly_defined.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/radish/reset_assignment.hpp>
#include <pstade/radish/swap_reset.hpp>
#include <pstade/radish/swappable.hpp>
#include "./any_fwd.hpp"
#include "./any_indexed_iterator.hpp"
#include "./iter_range.hpp"
#include "./lightweight_copyable.hpp"
#include "./range_difference.hpp"
#include "./range_reference.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace any_indexed_detail {


    template< class Reference, class Value, class Difference >
    struct super_
    {
        typedef
            iter_range<
                any_indexed_iterator<Reference, Value, Difference>,
                radish::swappable    < any_indexed<Reference, Value, Difference>,
                lightweight_copyable < any_indexed<Reference, Value, Difference> > >
            >
        type;
    };


    template< class Super, class Iterator > inline
    Super make(Iterator first, Iterator last)
    {
        typedef typename Super::iterator iter_t;
        return Super(iter_t(0, first), iter_t(last - first, first));
    }


} // namespace any_indexed_detail


template< class Reference, class Value, class Difference >
struct any_indexed :
    any_indexed_detail::super_<Reference, Value, Difference>::type
{
private:
    typedef any_indexed self_t;
    typedef typename any_indexed_detail::super_<Reference, Value, Difference>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    typedef typename iter_t::index_type index_type;

// structors (This order matters in buggy msvc-7.1.)
    template< class R, class V, class D >
    any_indexed(any_indexed<R, V, D> const& other,
        typename enable_if< is_convertible_to_any_indexed_iterator<typename any_indexed<R, V, D>::iterator, iter_t> >::type = 0
    ) :
        super_t(any_indexed_detail::make<super_t>(boost::begin(other), boost::end(other)))
    { }

    template< class It, class Ij >
    any_indexed(iter_range<It, Ij> const& rng,
        typename enable_if< is_convertible_to_any_indexed_iterator<It, iter_t> >::type = 0
    ) :
        super_t(any_indexed_detail::make<super_t>(boost::begin(rng), boost::end(rng)))
    { }

    any_indexed(boost::none_t = boost::none)
    { }

    template< class Range >
    explicit any_indexed(Range& rng, typename disable_if_copy<self_t, Range>::type = 0) :
        super_t(any_indexed_detail::make<super_t>(boost::begin(rng), boost::end(rng)))
    { }

    template< class Range >
    explicit any_indexed(Range const& rng) :
        super_t(any_indexed_detail::make<super_t>(boost::begin(rng), boost::end(rng)))
    { }

    any_indexed(T_as_type_erasure, self_t const& rng) :
        super_t(any_indexed_detail::make<super_t>(boost::begin(rng), boost::end(rng)))
    { }

// assignments
    typedef any_indexed pstade_radish_this_type;
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
    PSTADE_IMPLICITLY_DEFINED_COPY_TO_BASE(any_indexed, super_t)
};


template< class Range >
struct any_indexed_of
{
    typedef
        any_indexed<
            typename range_reference<Range>::type,
            typename range_value<Range>::type,
            typename range_difference<Range>::type
        >
    type;
};


typedef
    egg::generator<
        any_indexed<
            range_reference<boost::mpl::_1>,
            range_value<boost::mpl::_1>,
            range_difference<boost::mpl::_1>
        > const
    >::type
T_make_any_indexed;

PSTADE_POD_CONSTANT((T_make_any_indexed), make_any_indexed) = PSTADE_EGG_GENERATOR();


} } // namespace pstade::oven


#endif
