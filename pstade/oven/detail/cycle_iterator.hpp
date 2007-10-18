#ifndef PSTADE_OVEN_DETAIL_CYCLE_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_CYCLE_ITERATOR_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <utility> // pair
#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/next_prior.hpp> // prior
#include <boost/type_traits/is_same.hpp>
#include <pstade/debug.hpp>


namespace pstade { namespace oven { namespace detail {


// cycle_iterator
//

template< class Difference >
std::pair<Difference, Difference> positive_rem_div(Difference a, Difference b)
{
    BOOST_ASSERT(b >= 0);

    Difference const q = a / b;
    Difference const r = a % b;
    if (r < 0)
        return std::make_pair(q - 1, r + b);
    else
        return std::make_pair(q, r);
}


template< class Iterator >
bool cycle_iter_find(Iterator first, Iterator last, Iterator val)
{
    debugging();

    for (; first != last; ++first) {
        if (first == val)
            return true;
    }

    return false;
}


template< class ForwardIter, class Incrementable >
struct cycle_iterator;


template< class ForwardIter, class Incrementable >
struct cycle_iterator_super
{
    typedef
        boost::iterator_adaptor<
            cycle_iterator<ForwardIter, Incrementable>,
            ForwardIter
        >
    type;
};


template< class ForwardIter, class Incrementable >
struct cycle_iterator :
    cycle_iterator_super<ForwardIter, Incrementable>::type
{
private:
    typedef typename cycle_iterator_super<ForwardIter, Incrementable>::type super_t;
    typedef typename super_t::difference_type diff_t;
    typedef typename super_t::reference ref_t;

public:
    typedef Incrementable count_type;

    cycle_iterator()
    { }

    cycle_iterator(
        ForwardIter it, Incrementable count,
        ForwardIter first, ForwardIter last
    ) :
        super_t(it), m_count(count),
        m_first(first), m_last(last)
    { }

template< class, class > friend struct cycle_iterator;
    template< class F, class I >
    cycle_iterator(cycle_iterator<F, I> const& other,
        typename boost::enable_if_convertible<F, ForwardIter>::type * = 0,
        typename boost::enable_if_convertible<I, Incrementable>::type * = 0
    ) :
        super_t(other.base()), m_count(other.m_count),
        m_first(other.m_first), m_last(other.m_last)
    { }

    count_type count() const
    {
        return m_count;
    }

private:
    count_type m_count;
    ForwardIter m_first, m_last;

    bool invariant() const
    {
#if defined(PSTADE_OVEN_TESTING)
        return detail::cycle_iter_find(m_first, m_last, this->base());
#else
        return true;
#endif
    }

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return m_first == other.m_first && m_last == other.m_last;
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT(invariant());
        BOOST_ASSERT(this->base() != m_last);

        return *this->base();
    }

    template< class F, class I >
    bool equal(cycle_iterator<F, I> const& other) const
    {
        BOOST_ASSERT(invariant());
        BOOST_ASSERT(is_compatible(other));

        return m_count == other.m_count && this->base() == other.base();
    }

    void increment()
    {
        BOOST_ASSERT(invariant());

        if (++this->base_reference() == m_last) {
            this->base_reference() = m_first;
            ++m_count;
        }
    }

    void decrement()
    {
        BOOST_ASSERT(invariant());

        if (this->base() == m_first) {
            this->base_reference() = m_last;
            --m_count;
        }

        --this->base_reference();
    }

    void advance(diff_t n)
    {
        BOOST_ASSERT(invariant());

        std::pair<diff_t, diff_t> const q_r =
            detail::positive_rem_div((this->base() - m_first) + n, m_last - m_first);
        BOOST_ASSERT(0 <= q_r.second);
        BOOST_ASSERT(q_r.second < m_last - m_first);

        this->base_reference() = m_first + q_r.second;
        m_count += q_r.first;
    }

    template< class F, class I >
    diff_t distance_to(cycle_iterator<F, I> const& other) const
    {
        BOOST_ASSERT(invariant());
        BOOST_ASSERT(is_compatible(other));

        return ((m_last - m_first) * (other.m_count - m_count)) + (other.base() - this->base());
    }
};


// has_cycle_count
//

template< class X >
struct is_cycle_iterator :
    boost::mpl::false_
{ };

template< class F, class I >
struct is_cycle_iterator< cycle_iterator<F, I> > :
    boost::mpl::true_
{ };


template< class CycleIter, class Incrementable >
struct has_cycle_count_aux :
    boost::is_same<typename CycleIter::count_type, Incrementable>
{ };

template< class X, class Incrementable >
struct has_cycle_count :
    boost::mpl::and_<
        is_cycle_iterator<X>,
        has_cycle_count_aux<X, Incrementable>
    >
{ };


} } } // namespace pstade::oven::detail


#endif
