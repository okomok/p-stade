#ifndef PSTADE_OVEN_DETAIL_SUCCEED_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_SUCCEED_ITERATOR_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <pstade/functional.hpp> // identity
#include <pstade/to_ref.hpp>
#include "../do_iter_swap.hpp"
#include "./constant_reference.hpp"
#include "./has_is_constant.hpp"
#include "./minimum_pure.hpp"
#include "./pure_traversal.hpp"


namespace pstade { namespace oven { namespace detail {


template< class Iterator, class Traversal = typename pure_traversal<Iterator>::type >
struct assert_not_old_return_op
{
    Iterator operator()(Iterator now) const
    {
        BOOST_ASSERT("iterator must be advanced." && m_old != now);
        return now;
    }

    explicit assert_not_old_return_op(Iterator old) :
        m_old(old)
    { }

private:
    Iterator m_old;
};

template< class Iterator >
struct assert_not_old_return_op<Iterator, boost::single_pass_traversal_tag> :
    op_identity
{
    explicit assert_not_old_return_op(Iterator)
    { }
};

#if !defined(NDEBUG)
template< class Iterator > inline
assert_not_old_return_op<Iterator> assert_not_old(Iterator old)
{
    return assert_not_old_return_op<Iterator>(old);
}
#else
template< class Iterator> inline
op_identity const& assert_not_old(Iterator)
{
    return identity;
}
#endif


template< class Iterator, class BinaryFun >
struct succeed_iterator;


template< class Iterator, class BinaryFun >
struct succeed_iterator_super
{
    typedef
        boost::iterator_adaptor<
            succeed_iterator<Iterator, BinaryFun>,
            Iterator,
            boost::use_default,
            typename minimum_pure<
                boost::forward_traversal_tag,
                typename boost::iterator_traversal<Iterator>::type
            >::type,
            typename boost::mpl::eval_if< has_is_constant<BinaryFun>,
                constant_reference<Iterator>,
                boost::mpl::identity<boost::use_default>
            >::type
        >
    type;
};


template< class Iterator, class BinaryFun >
struct succeed_iterator :
    succeed_iterator_super<Iterator, BinaryFun>::type
{
private:
    typedef typename succeed_iterator_super<Iterator, BinaryFun>::type super_t;
    typedef typename super_t::reference ref_t;

public:
    succeed_iterator()
    { }

    succeed_iterator(Iterator it, BinaryFun elect, Iterator last) :
        super_t(it), m_elect(elect), m_last(last)
    { }

    template< class F >
    succeed_iterator(succeed_iterator<F, BinaryFun> const& other,
        typename boost::enable_if_convertible<F, Iterator>::type * = 0
    ) :
        super_t(other.base()), m_elect(other.elect()), m_last(other.end())
    { }

    BinaryFun elect() const
    {
        return m_elect;
    }

    Iterator end() const
    {
        return m_last;
    }

private:
    BinaryFun m_elect;
    Iterator m_last;

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return m_last == other.end();
    }

    bool is_end() const
    {
        return this->base() == m_last;
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT(!is_end());
        return *this->base();
    }

    template< class F >
    bool equal(succeed_iterator<F, BinaryFun> const& other) const
    {
        BOOST_ASSERT(is_compatible(other));
        return this->base() == other.base();
    }

    void increment()
    {
        BOOST_ASSERT(!is_end());
        this->base_reference() = detail::assert_not_old(this->base())(
            m_elect(this->base(), to_cref(m_last))
        );
    }
};


template< class F1, class B1, class F2, class B2 > inline
void iter_swap(succeed_iterator<F1, B1> it1, succeed_iterator<F2, B2> it2, int = 0)
{
    do_iter_swap(it1.base(), it2.base());
}


} } } // namespace pstade::oven::detail


#endif

