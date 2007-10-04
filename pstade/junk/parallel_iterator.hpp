#ifndef PSTADE_OVEN_DETAIL_PARALLEL_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_PARALLEL_ITERATOR_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <pstade/mutex_lockable.hpp>
#include "../do_iter_swap.hpp"


namespace pstade { namespace oven { namespace detail {


template< class Iterator >
struct parallel_memo :
    mutex_lockable
{
    Iterator iter;
};


template< class Iterator, class MemoPtr >
struct parallel_iterator;


template< class Iterator >
struct parallel_iterator_super
{
    typedef
        boost::iterator_facade<
            parallel_iterator<Iterator, MemoPtr>,
            typename boost::iterator_value<Iterator>::type,
            typename boost::iterator_traversal<Iterator>::type,
            typename boost::iterator_reference<Iterator>::type,
            typename boost::iterator_difference<Iterator>::type
        >
    type;
};


template< class Iterator, class MemoPtr >
struct parallel_iterator :
    parallel_iterator_super<Iterator, MemoPtr>::type
{
private:
    typedef typename parallel_iterator_super<Iterator, MemoPtr>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::difference_type diff_t;

public:
    typedef typename boost::pointee<MemoPtr>::type memo_type;

    parallel_iterator()
    { }

    parallel_iterator(Iterator it, MemoPtr const& pmemo) :
        super_t(it), m_pmemo(memo)
    { }

    parallel_iterator& operator=(parallel_iterator const& other)
    {
        typename memo_type::scoped_lock_type lock(m_pmemo->mutex());
        m_pmemo->base_reference() = other->base();
    }

private:
    MemoPtr m_pmemo;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        typename memo_type::scoped_lock_type lock(m_pmemo->mutex());
        return *this->base();
    }

    bool equal(self_t const& other) const
    {
        typename memo_type::scoped_lock_type lock(m_pmemo->mutex());
        return this->base() == other.base();
    }

    void increment()
    {
        typename memo_type::scoped_lock_type lock(m_pmemo->mutex());
        ++this->base_reference();
    }

    void decrement()
    {
        typename memo_type::scoped_lock_type lock(m_pmemo->mutex());
        --this->base_reference();
    }

    void advance(diff_t n)
    {
        typename memo_type::scoped_lock_type lock(m_pmemo->mutex());
        this->base_reference() += n;
    }

    diff_t distance_to(self_t const& other) const
    {
        typename memo_type::scoped_lock_type lock(m_pmemo->mutex());
        return other.base() - this->base();
    }
};


template< class I1, class I2 >
void iter_swap(parallel_iterator<I1> it1, parallel_iterator<I2> it2, int = 0)
{
    detail::parallel_singularity(it1);
    detail::parallel_singularity(it2);
    do_iter_swap(it1.base(), it2.base());
}


} } } // namespace pstade::oven::detail


#endif
