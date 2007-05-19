#ifndef PSTADE_OVEN_ANY_RANGE_HPP
#define PSTADE_OVEN_ANY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_categories.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/disable_if_copy.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/implicitly_defined.hpp>
#include <pstade/object_generator.hpp>
#include "./any_iterator.hpp"
#include "./iter_range.hpp"
#include "./lightweight_copyable.hpp"
#include "./range_difference.hpp"
#include "./range_reference.hpp"
#include "./range_traversal.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


template< class Reference, class Traversal, class Value, class Difference >
struct any_range;


namespace any_range_detail {


    template< class Reference, class Traversal, class Value, class Difference >
    struct super_
    {
        typedef
            iter_range<
                any_iterator<Reference, Traversal, Value, Difference>,
                // Copying ForwardRange needs 'new', hence not considered "lightweight".
                lightweight_copyable<
                    any_range<Reference, boost::single_pass_traversal_tag, Value, Difference>
                >
            >
        type;
    };


} // namespace any_range_detail


template<
    class Reference,
    class Traversal,
    class Value      = boost::use_default,
    class Difference = boost::use_default
>
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


PSTADE_OBJECT_GENERATOR(make_any_range,
     (any_range< range_reference<_1>, range_pure_traversal<_1>, range_value<_1>, range_difference<_1> >) const)



} } // namespace pstade::oven


// For some reason, 'lightweight_copyable' doesn't work under msvc.
// This is required only if namespace 'oven' is in 'boost'.

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))

    #include <boost/foreach.hpp>
    #include <boost/mpl/bool.hpp>

    namespace boost { namespace foreach {

        template< class Reference, class Value, class Difference >
        struct is_lightweight_proxy< pstade::oven::any_range<Reference, single_pass_traversal_tag, Value, Difference> > :
            boost::mpl::true_
        { };

    } } // namespace boost::foreach

#endif


#endif
