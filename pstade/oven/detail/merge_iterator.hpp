#ifndef PSTADE_OVEN_DETAIL_MERGE_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_MERGE_ITERATOR_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/config.hpp> // BOOST_NESTED_TEMPLATE
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_warning.hpp>
#include <pstade/do_swap.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/is_returnable.hpp>
#include <pstade/to_ref.hpp>
#include "../is_sorted.hpp"
#include "../read.hpp"
#include "./constant_reference.hpp"
#include "./minimum_pure.hpp"


namespace pstade { namespace oven { namespace detail {


template<
    class Iterator1, class Iterator2,
    class Compare,
    class MergeRoutine
>
struct merge_iterator;


template< class Iterator1, class Iterator2 >
struct merge_iterator_traversal :
    minimum_pure<
        boost::forward_traversal_tag,
        typename minimum_pure<
            typename boost::iterator_traversal<Iterator1>::type,
            typename boost::iterator_traversal<Iterator2>::type
        >::type
    >
{ };


template<
    class Iterator1, class Iterator2,
    class Compare,
    class MergeRoutine
>
struct merge_iterator_super
{
    typedef
        boost::iterator_adaptor<
            merge_iterator<Iterator1, Iterator2, Compare, MergeRoutine>,
            Iterator1,
            boost::use_default,
            typename merge_iterator_traversal<Iterator1, Iterator2>::type,
            typename constant_reference<Iterator1>::type
        >
    type;
};


template<
    class Iterator1, class Iterator2,
    class Compare,
    class MergeRoutine
>
struct merge_iterator :
    merge_iterator_super<Iterator1, Iterator2, Compare, MergeRoutine>::type
{
private:
    typedef typename merge_iterator_super<Iterator1, Iterator2, Compare, MergeRoutine>::type super_t;
    typedef typename super_t::reference ref_t;

public:
    merge_iterator()
    { }

    merge_iterator(
        Iterator1 it1, Iterator1 last1,
        Iterator2 it2, Iterator2 last2,
        Compare comp
    ) :
        super_t(it1), m_last1(last1),
        m_it2(it2),   m_last2(last2),
        m_comp(comp)
    {
        // "./jointed.hpp" tells why this is at function scope.
        BOOST_MPL_ASSERT((is_convertible<typename iterator_read<Iterator2>::type, ref_t>));
        BOOST_STATIC_WARNING((is_returnable<typename iterator_read<Iterator2>::type, ref_t>::value));

#if defined(PSTADE_OVEN_TESTING)
        BOOST_ASSERT(is_sorted(make_iter_range(it1, last1), comp));
        BOOST_ASSERT(is_sorted(make_iter_range(it2, last2), comp));
#endif

        MergeRoutine::before_yield(
            this->base_reference(), to_cref(m_last1), m_it2, to_cref(m_last2), to_cref(m_comp));
    }

template< class, class, class, class > friend struct merge_iterator;
    template< class I1, class I2 >
    merge_iterator(merge_iterator<I1, I2, Compare, MergeRoutine> const& other,
        typename boost::enable_if_convertible<I1, Iterator1>::type * = 0,
        typename boost::enable_if_convertible<I2, Iterator2>::type * = 0
    ) :
        super_t(other.base()), m_last1(other.m_last1), 
        m_it2(other.m_it2),    m_last2(other.m_last2),
        m_comp(other.m_comp)
    { }

private:
    Iterator1 m_last1;
    Iterator2 m_it2, m_last2;
    Compare m_comp;

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return m_last1 == other.m_last1 && m_last2 == other.m_last2;
    }

    bool is_end1() const
    {
        return this->base() == m_last1;
    }

    bool is_end2() const
    {
        return m_it2 == m_last2;
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT(!(is_end1() && is_end2()));
        return MergeRoutine::BOOST_NESTED_TEMPLATE yield<ref_t>(
            this->base(), m_last1, m_it2, m_last2, m_comp);
    }

    template< class I1, class I2 >
    bool equal(merge_iterator<I1, I2, Compare, MergeRoutine> const& other) const
    {
        BOOST_ASSERT(is_compatible(other));
        return this->base() == other.base() && m_it2 == other.m_it2;
    }

    void increment()
    {
        BOOST_ASSERT(!(is_end1() && is_end2()));

        Iterator1 first1(this->base()); // for exception safety
        Iterator2 first2(m_it2);        //

        MergeRoutine::after_yield( first1, to_cref(m_last1), first2, to_cref(m_last2), to_cref(m_comp));
        MergeRoutine::before_yield(first1, to_cref(m_last1), first2, to_cref(m_last2), to_cref(m_comp));

        do_swap(first1, this->base_reference());
        do_swap(first2, m_it2);
    }
};


} } } // namespace pstade::oven::detail


#endif
