#ifndef PSTADE_SAUSAGE_YIELD_ITERATOR_HPP
#define PSTADE_SAUSAGE_YIELD_ITERATOR_HPP


// PStade.Sausage
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// *Routine* is a unary functor which has nested 'routine_result_type',
// and its 'operator()' takes a unary functor as templated argument.
// See <tomato/window/for_each_child_window.hpp> as an example.
// This iterator was originally implemeted by
// http://d.hatena.ne.jp/y-hamigaki/20060409#1144593955


#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/unused.hpp>
#include "./detail/routine_result.hpp"
#include "./detail/yield_iterator_impl.hpp"


namespace pstade { namespace sausage {


template< class Routine >
struct yield_iterator;


namespace yield_iterator_detail {


    template< class Routine >
    struct super_
    {
        typedef typename detail::routine_result<Routine>::type result_t;
        typedef typename remove_cvr<result_t>::type val_t;
        typedef typename pass_by_reference<result_t>::type ref_t;

        typedef boost::iterator_facade<
            yield_iterator<Routine>,
            val_t,
            boost::single_pass_traversal_tag,
            ref_t
        > type;
    };


} // namespace yield_iterator_detail


template< class Routine >
struct yield_iterator :
    yield_iterator_detail::super_<Routine>::type
{
private:
    typedef typename yield_iterator_detail::super_<Routine>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef detail::yield_iterator_impl<Routine> impl_t;

public:
    explicit yield_iterator() // end iter
    { }

    explicit yield_iterator(Routine const& rou) :
        m_pimpl(new impl_t(rou))
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

    template< class Other >
    bool equal(Other const& other) const
    {
        return m_pimpl == other.m_pimpl;
    }
};


template< class Routine > inline
yield_iterator<Routine> const
make_yield_begin_iterator(Routine rou)
{
    return yield_iterator<Routine>(rou);
}


template< class Routine > inline
yield_iterator<Routine> const
make_yield_end_iterator(Routine rou)
{
    pstade::unused(rou);
    return yield_iterator<Routine>();
}


} } // namespace pstade::sausage


#endif
