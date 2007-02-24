#ifndef PSTADE_OVEN_ANY_RANGE_HPP
#define PSTADE_OVEN_ANY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // ptrdiff_t
#include <boost/iterator/iterator_categories.hpp>
#include <pstade/disable_if_copy.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/implicitly_defined.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/use_default.hpp>
#include "./any_iterator.hpp"
#include "./as_lightweight_proxy.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./range_reference.hpp"
#include "./range_traversal.hpp"
#include "./range_value.hpp"


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
                any_iterator<
                    Reference,
                    Traversal,
                    typename use_default_eval_to< Value, remove_cvr<Reference> >::type,
                    typename use_default_to<Difference, std::ptrdiff_t>::type
                >
            >
        type;
    };


    struct nobody;


} // namespace any_range_detail


template<
    class Reference,
    class Traversal,
    class Value      = boost::use_default,
    class Difference = boost::use_default,
    class BaseRange  = any_range_detail::nobody // for implicit conversion
>
struct any_range :
    any_range_detail::super_<Reference, Traversal, Value, Difference>::type,
    private as_lightweight_proxy< any_range<Reference, boost::single_pass_traversal_tag, Value, Difference, BaseRange> >
{
private:
    typedef any_range self_t;
    typedef typename any_range_detail::super_<Reference, Traversal, Value, Difference>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
// structors
    any_range()
    { }

    template< class R, class T, class V, class D, class B >
    any_range(any_range<R, T, V, D, B> const& other,
        typename enable_if< is_convertible_to_any_iterator<typename any_range<R, T, V, D, B>::iterator, iter_t> >::type = 0
    ) :
        super_t(boost::begin(other), boost::end(other))
    { }

    template< class I >
    any_range(iter_range<I> const& rng,
        typename enable_if< is_convertible_to_any_iterator<I, iter_t> >::type = 0
    ) :
        super_t(boost::begin(rng), boost::end(rng))
    { }

    any_range(BaseRange& rng) :
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

// assignments
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


template< class BaseRange >
struct any_range_of
{
    typedef
        any_range<
            typename range_reference<BaseRange>::type,
            typename range_pure_traversal<BaseRange>::type,
            typename range_value<BaseRange>::type,
            typename range_difference<BaseRange>::type,
            BaseRange
        >
    type;
};


} } // namespace pstade::oven


#endif
