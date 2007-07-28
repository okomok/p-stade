#ifndef PSTADE_OVEN_DETAIL_BLOCK_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_BLOCK_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// *IteratorBlock* is a unary functor which has nested 'yield_type',
// and its 'operator()' takes a unary functor as templated argument.
// See <gravy/for_each_child_window.hpp> as an example.
// This iterator was originally implemented by
// http://d.hatena.ne.jp/y-hamigaki/20060409#1144593955


#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/remove_cvr.hpp>
#include "./block_iterator_impl.hpp"


namespace pstade { namespace oven { namespace detail {


template< class IteratorBlock >
struct block_iterator;


template< class IteratorBlock >
struct block_iterator_super
{
    typedef typename IteratorBlock::yield_type result_t;
    typedef typename remove_cvr<result_t>::type val_t;
    typedef typename pass_by_reference<result_t>::type ref_t;

    typedef boost::iterator_facade<
        block_iterator<IteratorBlock>,
        val_t,
        boost::single_pass_traversal_tag,
        ref_t
    > type;
};


template< class IteratorBlock >
struct block_iterator :
    block_iterator_super<IteratorBlock>::type
{
private:
    typedef block_iterator self_t;
    typedef typename block_iterator_super<IteratorBlock>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef block_iterator_impl<IteratorBlock> impl_t;

public:
    explicit block_iterator() // the end iterator
    { }

    explicit block_iterator(IteratorBlock block) :
        m_pimpl(new impl_t(block))
    {
        if (m_pimpl->done())
            m_pimpl.reset();
    }

private:
    boost::shared_ptr<impl_t> m_pimpl;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        return m_pimpl->deref();
    }

    void increment()
    {
        m_pimpl->next();
        if (m_pimpl->done())
            m_pimpl.reset();
    }

    bool equal(self_t const& other) const
    {
        return m_pimpl == other.m_pimpl;
    }
};


} } } // namespace pstade::oven::detail


#endif
