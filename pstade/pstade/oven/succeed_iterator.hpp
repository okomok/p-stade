#ifndef PSTADE_OVEN_SUCCEED_ITERATOR_HPP
#define PSTADE_OVEN_SUCCEED_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <pstade/as.hpp>
#include <pstade/has_xxx.hpp>
#include <pstade/if_debug.hpp>
#include <pstade/object_generator.hpp>
#include "./detail/constant_reference.hpp"
#include "./detail/pure_traversal.hpp"


namespace pstade { namespace oven {


template< class Iterator, class Council >
struct succeed_iterator;


namespace succeed_iterator_detail {


    PSTADE_HAS_TYPE(is_constant)


    template< class Iterator, class Council >
    struct super_
    {
        typedef
            boost::iterator_adaptor<
                succeed_iterator<Iterator, Council>,
                Iterator,
                boost::use_default,
                typename Council::template traversal<
                    typename detail::pure_traversal<Iterator>::type
                >::type,
                typename boost::mpl::eval_if< has_is_constant<Council>,
                    detail::constant_reference<Iterator>,
                    boost::mpl::identity<boost::use_default>
                >::type
            >
        type;
    };


} // namespace succeed_iterator_detail


template< class Iterator, class Council >
struct succeed_iterator :
    succeed_iterator_detail::super_<Iterator, Council>::type
{
private:
    typedef typename succeed_iterator_detail::super_<Iterator, Council>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::difference_type diff_t;

public:
    succeed_iterator()
    { }

    succeed_iterator(Iterator const& it, Council const& council, Iterator const& last) :
        super_t(it), m_council(council), m_last(last)
    { }

    template< class F >
    succeed_iterator(succeed_iterator<F, Council> const& other,
        typename boost::enable_if_convertible<F, Iterator>::type * = 0
    ) :
        super_t(other.base()), m_council(other.council()), m_last(other.end())
    { }

    Council const& council() const
    {
        return m_council;
    }

    Iterator const& end() const
    {
        return m_last;
    }

private:
    Council m_council;
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
    bool equal(succeed_iterator<F, Council> const& other) const
    {
        BOOST_ASSERT(is_compatible(other));
        return this->base() == other.base();
    }

    void increment()
    {
        BOOST_ASSERT(!is_end());
        this->base_reference() = m_council.increment(this->base(), as_cref(m_last));
    }

    void decrement()
    {
        this->base_reference() = m_council.decrement(this->base(), as_cref(m_last));
    }

    void advance(diff_t const& d)
    {
        BOOST_ASSERT(0 < d ? !is_end() : true);
        this->base_reference() = m_council.advance(this->base(), d, as_cref(m_last));
    }

    template< class F >
    diff_t distance_to(succeed_iterator<F, Council> const& other) const
    {
        BOOST_ASSERT(is_compatible(other));
        return m_council.template difference<diff_t>(this->base(), other.base(), m_last);
    }
};


PSTADE_OBJECT_GENERATOR(make_succeed_iterator,
    (succeed_iterator< deduce<_1, to_value>, deduce<_2, to_value> >) const)


} } // namespace pstade::oven


#endif
