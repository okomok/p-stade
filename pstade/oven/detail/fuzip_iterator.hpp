#ifndef PSTADE_OVEN_DETAIL_FUZIP_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_FUZIP_ITERATOR_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright David Abrahams and Thomas Becker 2000-2006. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/sequence/comparison.hpp>
#include <boost/fusion/sequence/conversion/as_vector.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/mpl.hpp> // lets FusionSequence be MPLSequence
#include <boost/mpl/placeholders.hpp> // missing from 'minimum_category.hpp'
#include <boost/iterator/detail/minimum_category.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform_view.hpp>
#include <pstade/remove_cvr.hpp>
#include "./pure_traversal.hpp"


namespace pstade { namespace oven { namespace detail {


struct increment_iterator
{
    template< class Iterator >
    void operator()(Iterator& it) const
    {
        ++it;
    }
};


struct decrement_iterator
{
    template< class Iterator >
    void operator()(Iterator& it) const
    {
        --it;
    }
};


template< class Difference >
struct advance_iterator
{
    template< class Iterator >
    void operator()(Iterator& it) const
    {
        it += m_n;
    }

    explicit advance_iterator(Difference n) :
        m_n(n)
    { }

private:
    Difference m_n;
};


struct dereference_iterator
{
    template< class FunCall >
    struct result;

    template< class Fun, class Iterator >
    struct result<Fun(Iterator)> :
        boost::iterator_reference<
            typename remove_cvr<Iterator>::type
        >
    { };

    // Pass by reference; see "../reverese_iterator.hpp"
    template< class Iterator >
    typename result<void(Iterator&)>::type
    operator()(Iterator& it) const
    {
        return *it;
    }
};


template< class IteratorTuple >
struct fuzip_iterator;


template< class IteratorTuple >
struct fuzip_iterator_super
{
    // Though an iterator whose 'reference' is a transform-view
    // seems conforming, such implementation would surprise some algorithms.

    typedef typename
        // 'as_vector' is required for 'value_type',
        // because a view refers to 'm_tuple' in an iterator.
        boost::fusion::result_of::as_vector<
            typename boost::fusion::result_of::transform<
                IteratorTuple const,
                dereference_iterator
            >::type const
        >::type
    val_t;

    typedef typename
        boost::iterator_difference<
            typename boost::mpl::front<IteratorTuple>::type
        >::type
    diff_t;

    typedef typename
        boost::mpl::fold<
            typename boost::mpl::transform_view< IteratorTuple, pure_traversal<boost::mpl::_1> >::type,
            boost::random_access_traversal_tag,
            boost::detail::minimum_category<boost::mpl::_1, boost::mpl::_2>
        >::type
    trv_t;

    typedef
        boost::iterator_facade<
            fuzip_iterator<IteratorTuple>,
            val_t,
            trv_t,
            val_t,
            diff_t
        >
    type;
};


template< class IteratorTuple >
struct fuzip_iterator :
    fuzip_iterator_super<IteratorTuple>::type
{
private:
    typedef typename fuzip_iterator_super<IteratorTuple>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::difference_type diff_t;

public:
    explicit fuzip_iterator()
    { }

    explicit fuzip_iterator(IteratorTuple const& tup) :
        m_tuple(tup)
    { }

    IteratorTuple const& iterator_tuple() const
    {
        return m_tuple;
    }

private:
    IteratorTuple m_tuple;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        return boost::fusion::as_vector(
            boost::fusion::transform(m_tuple, dereference_iterator())
        );
    }

    template< class I >
    bool equal(fuzip_iterator<I> const& other) const
    {
        return m_tuple == other.iterator_tuple();
    }

    void increment()
    {
        boost::fusion::for_each(m_tuple, increment_iterator());
    }

    void decrement()
    {
        boost::fusion::for_each(m_tuple, decrement_iterator());
    }

    void advance(diff_t n)
    {
        boost::fusion::for_each(m_tuple, advance_iterator<diff_t>(n));
    }

    template< class I >
    diff_t distance_to(fuzip_iterator<I> const& other) const
    {
        return boost::fusion::deref(boost::fusion::begin(other.iterator_tuple()))
            - boost::fusion::deref(boost::fusion::begin(m_tuple));
    }
};


} } } // namespace pstade::oven::detail


#endif
