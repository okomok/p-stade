#ifndef PSTADE_OVEN_MERGED_HPP
#define PSTADE_OVEN_MERGED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This range is Constant.
// If a value referenced by this iterator is changed,
// the incementing way is changed.
// Then, the iterators become incompatible.


#include <boost/assert.hpp>
#include <boost/config.hpp> // BOOST_NESTED_TEMPLATE
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/static_warning.hpp>
#include <pstade/as.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/do_swap.hpp>
#include <pstade/functional.hpp> // less
#include <pstade/is_convertible.hpp>
#include <pstade/is_returnable.hpp>
#include <pstade/pipable.hpp>
#include <pstade/unused.hpp>
#include "./concepts.hpp"
#include "./detail/constant_reference.hpp"
#include "./detail/minimum_pure.hpp"
#include "./is_sorted.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace merged_detail {


    namespace here = merged_detail;


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
            Iterator1& first1, Iterator1 last1,
            Iterator2& first2, Iterator2 last2,
            Compare comp)
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
            Iterator1 first1, Iterator1 last1,
            Iterator2 first2, Iterator2 last2,
            Compare comp)
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
            Iterator1& first1, Iterator1 last1,
            Iterator2& first2, Iterator2 last2,
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


    template<
        class Iterator1, class Iterator2,
        class Compare,
        class MergeRoutine
    >
    struct merge_iterator;


    template< class Iterator1, class Iterator2 >
    struct traversal_of :
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
    struct merge_iterator_super
    {
        typedef
            boost::iterator_adaptor<
                merge_iterator<Iterator1, Iterator2, Compare, MergeRoutine>,
                Iterator1,
                boost::use_default,
                typename traversal_of<Iterator1, Iterator2>::type,
                typename detail::constant_reference<Iterator1>::type
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
            Compare comp = less
        ) :
            super_t(it1), m_last1(last1),
            m_it2(it2),   m_last2(last2),
            m_comp(comp)
        {
            // "./jointed.hpp" tells why this is at function scope.
            BOOST_MPL_ASSERT((is_convertible<typename boost::iterator_reference<Iterator2>::type, ref_t>));
            BOOST_STATIC_WARNING((is_returnable<typename boost::iterator_reference<Iterator2>::type, ref_t>::value));

#if defined(PSTADE_OVEN_TESTS_SAMPLE_RANGES)
            BOOST_ASSERT(is_sorted(make_iter_range(it1, last1), comp));
            BOOST_ASSERT(is_sorted(make_iter_range(it2, last2), comp));
#endif

            MergeRoutine::before_yield(
                this->base_reference(), as_cref(m_last1), m_it2, as_cref(m_last2), as_cref(m_comp));
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

            MergeRoutine::after_yield( first1, as_cref(m_last1), first2, as_cref(m_last2), as_cref(m_comp));
            MergeRoutine::before_yield(first1, as_cref(m_last1), first2, as_cref(m_last2), as_cref(m_comp));

            do_swap(first1, this->base_reference());
            do_swap(first2, m_it2);
        }
    };


} // namespace merged_detail


template< class MergeRoutine = merged_detail::merge_routine >
struct op_make_merged :
    callable< op_make_merged<MergeRoutine> >
{
    template< class Myself, class Range1, class Range2, class Compare = op_less const >
    struct apply
    {
        typedef
            merged_detail::merge_iterator<
                typename range_iterator<Range1>::type,
                typename range_iterator<Range2>::type,
                typename pass_by_value<Compare>::type,
                MergeRoutine
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class Range1, class Range2, class Compare >
    Result call(Range1& rng1, Range2& rng2, Compare& comp) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range1>));
        PSTADE_CONCEPT_ASSERT((SinglePass<Range2>));

        typedef typename Result::iterator iter_t;
        return Result(
            iter_t(boost::begin(rng1), boost::end(rng1), boost::begin(rng2), boost::end(rng2), comp),
            iter_t(boost::end(rng1),   boost::end(rng1), boost::end(rng2),   boost::end(rng2), comp)
        );
    }

    template< class Result, class Range1, class Range2 >
    Result call(Range1& rng1, Range2& rng2) const
    {
        return (*this)(rng1, rng2, less);
    }
};


PSTADE_CONSTANT(make_merged, (op_make_merged<>))
PSTADE_PIPABLE(merged, (op_make_merged<>))


} } // namespace pstade::oven


#endif
