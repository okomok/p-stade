#ifndef PSTADE_OVEN_MERGE_ITERATOR_HPP
#define PSTADE_OVEN_MERGE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This iterator seems never mutable.
// If a value referenced by this iterator is changed,
// the incementing way is changed.
// Then, the iterators become incompatible.


#include <boost/assert.hpp>
#include <boost/config.hpp> // BOOST_NESTED_TEMPLATE
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_warning.hpp>
#include <pstade/do_swap.hpp>
#include <pstade/functional.hpp> // less
#include <pstade/is_convertible.hpp>
#include <pstade/is_returnable.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/unused.hpp>
#include "./detail/constant_reference.hpp"
#include "./detail/minimum_pure.hpp"
#include "./is_sorted.hpp"


namespace pstade { namespace oven {


template<
    class Iterator1, class Iterator2,
    class Compare,
    class MergeRoutine
>
struct merge_iterator;


namespace merge_iterator_detail {


    namespace here = merge_iterator_detail;


    template< class Iterator1, class Iterator2 >
    struct traversal :
        detail::minimum_pure<
            boost::forward_traversal_tag,
            typename detail::minimum_pure<
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
    struct super_
    {
        typedef
            boost::iterator_adaptor<
                merge_iterator<Iterator1, Iterator2, Compare, MergeRoutine>,
                Iterator1,
                boost::use_default,
                typename traversal<Iterator1, Iterator2>::type,
                typename detail::constant_reference<Iterator1>::type
            >
        type;
    };


    template< class X, class Y, class Compare > 
    X const& min_(X const& x, Y const& y, Compare comp)
    {
        // ternary-operator could make a rvalue.
        // I don't certainly know, though.

        // Standard requires 'x' if equal.
        if (comp(y, x))
            return y;
        else
            return x;
    }


    // This code is generated from STL implementation
    // somewhat by rote.
    struct merge_routine
    {
        template< class Iterator1, class Iterator2, class Compare >
        static void before_yield(
            Iterator1& first1, Iterator1 const& last1,
            Iterator2& first2, Iterator2 const& last2,
            Compare& comp)
        {
            /* has no effect.
            while (first1 != last1 && first2 != last2) {
                if (comp(*first2, *first1)) 
                    break;
                else
                    break;
            }
            */
            unused(first1, last1, first2, last2, comp);
        }

        template< class Reference, class Iterator1, class Iterator2, class Compare >
        static Reference yield(
            Iterator1 const& first1, Iterator1 const& last1,
            Iterator2 const& first2, Iterator2 const& last2,
            Compare& comp)
        {
            // copy-copy phase
            if (first1 == last1)
                return *first2;
            else if (first2 == last2)
                return *first1;

            // while phase
            return here::min_(*first1, *first2, comp);
        }

        template< class Iterator1, class Iterator2, class Compare >
        static void after_yield(
            Iterator1& first1, Iterator1 const& last1,
            Iterator2& first2, Iterator2 const& last2,
            Compare comp)
        {
            // copy-copy phase
            if (first1 == last1) {
                ++first2;
                return;
            }
            else if (first2 == last2) {
                ++first1;
                return;
            }

            // while phase
            if (comp(*first2, *first1))
                ++first2;
            else
                ++first1;
        }
    };


} // namespace merge_iterator_detail


template<
    class Iterator1, class Iterator2,
    class Compare      = op_less,
    class MergeRoutine = merge_iterator_detail::merge_routine
>
struct merge_iterator :
    merge_iterator_detail::super_<Iterator1, Iterator2, Compare, MergeRoutine>::type
{
private:
    typedef typename merge_iterator_detail::super_<Iterator1, Iterator2, Compare, MergeRoutine>::type super_t;
    typedef typename super_t::reference ref_t;

public:
    merge_iterator()
    { }

    merge_iterator(
        Iterator1 const& it1, Iterator1 const& last1,
        Iterator2 const& it2, Iterator2 const& last2,
        Compare const& comp = less
    ) :
        super_t(it1), m_last1(last1),
        m_it2(it2),   m_last2(last2),
        m_comp(comp)
    {
        // "./joint_iterator.hpp" tells why this is at function scope.
        BOOST_MPL_ASSERT((is_convertible<typename boost::iterator_reference<Iterator2>::type, ref_t>));
        BOOST_STATIC_WARNING((is_returnable<typename boost::iterator_reference<Iterator2>::type, ref_t>::value));

        // ranges may be too long to diagnose.
        // BOOST_ASSERT(is_sorted(it1, last1, comp));
        // BOOST_ASSERT(is_sorted(it2, last2, comp));
 
        MergeRoutine::before_yield(
            this->base_reference(), m_last1, m_it2, m_last2, m_comp);
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

        MergeRoutine::after_yield( first1, m_last1, first2, m_last2, m_comp);
        MergeRoutine::before_yield(first1, m_last1, first2, m_last2, m_comp);

        do_swap(first1, this->base_reference());
        do_swap(first2, m_it2);
    }
};


PSTADE_OBJECT_GENERATOR(make_merge_iterator,
    (merge_iterator< deduce<_1, to_value>, deduce<_2, to_value>, deduce<_3, to_value> >) const)


} } // namespace pstade::oven


#endif
