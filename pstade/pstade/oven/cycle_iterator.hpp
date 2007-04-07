#ifndef PSTADE_OVEN_CYCLE_ITERATOR_HPP
#define PSTADE_OVEN_CYCLE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Strictly speaking, this iterator is never be RandomAccessIterator,
// but RandomAccessTraversal. So is 'boost::counting_iterator'.
// Also note <boost-sandbox/boost/view/cyclic_iterator.hpp>.


#include <utility> // pair
#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/next_prior.hpp> // prior
#include <pstade/object_generator.hpp>
#include <pstade/value_convert.hpp>
#include "./detail/constant_reference.hpp"


namespace pstade { namespace oven {


template< class ForwardIter, class Incrementable >
struct cycle_iterator;


namespace cycle_iterator_detail {


    template< class ForwardIter, class Incrementable >
    struct super_
    {
        typedef
            boost::iterator_adaptor<
                cycle_iterator<ForwardIter, Incrementable>,
                ForwardIter,
                boost::use_default,
                boost::use_default,
                typename detail::constant_reference<ForwardIter>::type
            >
        type;
    };


    template< class Difference > inline
    std::pair<Difference, Difference> positive_rem_div(Difference const& a, Difference const& b)
    {
        BOOST_ASSERT(b >= 0);

        Difference const q = a / b;
        Difference const r = a % b;
        if (r < 0)
            return std::make_pair(q - 1, r + b);
        else
            return std::make_pair(q, r);
    }


} // namespace cycle_iterator_detail


template< class ForwardIter, class Incrementable >
struct cycle_iterator :
    cycle_iterator_detail::super_<ForwardIter, Incrementable>::type
{
private:
    typedef typename cycle_iterator_detail::super_<ForwardIter, Incrementable>::type super_t;
    typedef typename super_t::difference_type diff_t;
    typedef typename super_t::reference ref_t;

public:
    typedef Incrementable count_type;

    cycle_iterator()
    { }

    cycle_iterator(
        ForwardIter const& it, Incrementable const& count,
        ForwardIter const& first, ForwardIter const& last
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

    count_type const& count() const
    {
        return m_count;
    }

private:
    count_type m_count;
    ForwardIter m_first, m_last;

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return m_first == other.m_first && m_last == other.m_last;
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        return *this->base();
    }

    template< class F, class I >
    bool equal(cycle_iterator<F, I> const& other) const
    {
        BOOST_ASSERT(is_compatible(other));
        return this->base() == other.base() && m_count == other.m_count;
    }

    void increment()
    {
        if (++this->base_reference() == m_last) {
            this->base_reference() = m_first;
            ++m_count;
        }
    }

    void decrement()
    {
        if (this->base() != m_first) {
            --this->base_reference();
        }
        else {
            this->base_reference() = boost::prior(m_last);
            --m_count;
        }
    }

    void advance(diff_t const& d)
    {
        std::pair<diff_t, diff_t> const q_r =
            cycle_iterator_detail::positive_rem_div((this->base() - m_first) + d, m_last - m_first);
        BOOST_ASSERT(q_r.second >= 0);

        this->base_reference() = m_first + q_r.second;
        m_count += pstade::value_convert<count_type>(q_r.first);
    }

    template< class F, class I >
    diff_t distance_to(cycle_iterator<F, I> const& other) const
    {
        BOOST_ASSERT(is_compatible(other));
        return ((m_last - m_first) * (other.m_count - m_count)) + (other.base() - this->base());
    }
};


PSTADE_OBJECT_GENERATOR(make_cycle_iterator,
    (cycle_iterator< deduce<_1, to_value>, deduce<_2, to_value> >) const)


} } // namespace pstade::oven


#endif
