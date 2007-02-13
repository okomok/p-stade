#ifndef PSTADE_OVEN_MEMOIZE_ITERATOR_HPP
#define PSTADE_OVEN_MEMOIZE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// <boost/spirit/iterator/multi_pass.hpp>


#include <deque>
#include <boost/any.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/clone_ptr.hpp>
#include <pstade/object_generator.hpp>


namespace pstade { namespace oven {


template< class Iterator, class IsRecursive >
struct memoize_iterator;


namespace memoize_iterator_detail {


    template< class Iterator, class IsRecursive >
    struct super_
    {
        typedef typename
            boost::iterator_value<Iterator>::type
        val_t;

        typedef
            boost::iterator_facade<
                memoize_iterator<Iterator, IsRecursive>,
                val_t,
                boost::forward_traversal_tag,
                val_t const&,
                typename boost::iterator_difference<Iterator>::type
            >
        type;
    };


    // A smart pointer is needed, because 'Iterator' may
    // be neither DefaultConstructible nor CopyAssignable.
    // In a recursive range, as 'Iterator' must live outside
    // of the range in order to avoid reference-cycles.
    template< class Iterator, class IsRecursive >
    struct smart_ptr :
        boost::mpl::if_< IsRecursive,
            Iterator *,
            boost::shared_ptr<Iterator>
        >            
    { };


} // namespace memoize_iterator_detail


template< class Iterator, class IsRecursive = boost::mpl::false_ >
struct memoize_iterator :
    memoize_iterator_detail::super_<Iterator, IsRecursive>::type
{
private:
    typedef typename memoize_iterator_detail::super_<Iterator, IsRecursive>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::value_type val_t;
    typedef typename memoize_iterator_detail::smart_ptr<Iterator, IsRecursive>::type pbase_t;
    typedef std::deque<val_t> table_t;
    typedef typename table_t::size_type index_t;

public:
    explicit memoize_iterator()
    { }

template< class, class > friend struct memoize_iterator;
    explicit memoize_iterator(Iterator const& it) :
        m_pbase(new Iterator(it)),
        m_ptable(new table_t()), m_index(0)
    {
        BOOST_MPL_ASSERT_NOT((IsRecursive));
    }

    explicit memoize_iterator(Iterator *pit) :
        m_pbase(pit),
        m_ptable(new table_t()), m_index(0)
    {
        BOOST_MPL_ASSERT((IsRecursive));
    }

// as adaptor
    typedef Iterator base_type;

    Iterator const& base() const
    {
        return *m_pbase;
    }

private:
    pbase_t m_pbase;
    boost::shared_ptr<table_t> m_ptable;
    typename table_t::size_type m_index;
    mutable boost::optional<val_t> m_cached_value;

    Iterator& base_reference()
    {
        return *m_pbase;
    }

    bool is_in_table() const
    {
        return m_index != m_ptable->size();
    }

    val_t const& cached_value() const
    {
        if (!m_cached_value)
            m_cached_value = *base();

        return *m_cached_value;        
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        if (is_in_table())
            return (*m_ptable)[m_index];
        else
            return cached_value();
    }

    template< class Other >
    bool equal(Other const& other) const
    {
        if (is_in_table() && other.is_in_table())
            return m_index == other.m_index;

        if (!is_in_table() && !other.is_in_table())
            return base() == other.base();

        return false;
    }

    void increment()
    {
        if (is_in_table()) {
            ++m_index;
        }
        else {
            m_ptable->push_back(cached_value());
            ++base_reference();
            ++m_index;
            m_cached_value.reset();
        }
    }
};


PSTADE_OBJECT_GENERATOR(make_memoize_iterator,
    (memoize_iterator< deduce<_1, to_value> >) const)


} } // namespace pstade::oven


#endif
