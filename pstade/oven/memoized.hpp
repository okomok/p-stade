#ifndef PSTADE_OVEN_MEMOIZED_HPP
#define PSTADE_OVEN_MEMOIZED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


/*=============================================================================
    Copyright (c) 2001, Daniel C. Nuffer
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/


// References:
//
// [1] Daniel C. Nuffer, multi_pass iterator, Boost.Spirit, 2001.
//     http://www.boost.org/libs/spirit/doc/multi_pass.html


// Differences from References[1]:
//
// 1. No unique-check; rarely unique in range.
// 2. No end-iterator-check; it seems redundant.


#include <deque>
#include <memory> // auto_ptr
#include <boost/assert.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/noncopyable.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/any_movable.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace memoized_detail {


    template< class Iterator >
    struct memo :
        private boost::noncopyable
    {
    private:
        typedef typename boost::iterator_value<Iterator>::type value_t;
        typedef std::deque<value_t> table_t;

    public:
        typedef typename table_t::size_type index_type;

        explicit memo(Iterator it) :
            m_base(it), m_baseIndex(0)
        { }

        bool is_in_table(index_type i) const
        {
            BOOST_ASSERT(invariant());
            BOOST_ASSERT(0 <= i && i <= m_baseIndex);
            return i != m_table.size();
        }

        value_t const& deref(index_type i)
        {
            BOOST_ASSERT(invariant());
            BOOST_ASSERT(0 <= i && i <= m_baseIndex);

            if (!is_in_table(i)) {
                BOOST_ASSERT(i == m_baseIndex && m_baseIndex == m_table.size());
                m_table.push_back(*m_base);
            }

            return m_table[i];
        }

        index_type next(index_type i)
        {
            BOOST_ASSERT(invariant());
            BOOST_ASSERT(0 <= i && i <= m_baseIndex);

            if (i == m_baseIndex) {
                if (m_baseIndex == m_table.size())
                        m_table.push_back(*m_base);

                ++m_base;
                ++m_baseIndex;
            }

            return i + 1;
        }

        Iterator base() const
        {
            BOOST_ASSERT(invariant());
            return m_base;
        }

    private:
        Iterator m_base;
        index_type m_baseIndex;
        table_t m_table;

        bool invariant() const
        {
            return m_baseIndex == m_table.size() || m_baseIndex + 1 == m_table.size();
        }
    };


    template< class Iterator, class IsRecursive >
    struct memoize_iterator;


    // In a recursive range, 'Iterator' must live outside
    // of the range in order to avoid reference-cycles.
    // Todo: 'xpressive::detail::tracking_ptr' can kick in?
    template< class Memo, class IsRecursive >
    struct ptr_of :
        boost::mpl::if_< IsRecursive,
            Memo *,
            boost::shared_ptr<Memo>
        >
    { };


    template< class Iterator, class IsRecursive >
    struct memoize_iterator_super
    {
        typedef typename
            boost::iterator_value<Iterator>::type
        value_t;

        typedef
            boost::iterator_facade<
                memoize_iterator<Iterator, IsRecursive>,
                value_t,
                boost::forward_traversal_tag,
                value_t const&,
                typename boost::iterator_difference<Iterator>::type
            >
        type;
    };


    template< class Iterator, class IsRecursive >
    struct memoize_iterator :
        memoize_iterator_super<Iterator, IsRecursive>::type
    {
    private:
        typedef typename memoize_iterator_super<Iterator, IsRecursive>::type super_t;
        typedef typename super_t::reference ref_t;
        typedef memo<Iterator> memo_t;
        typedef typename ptr_of<memo_t, IsRecursive>::type pmemo_t;

    public:
        typedef memo_t memo_type;

        explicit memoize_iterator()
        { }

        explicit memoize_iterator(pmemo_t const& pmemo) :
            m_pmemo(pmemo), m_index(0)
        { }

    // as adaptor
        typedef Iterator base_type;

        Iterator base() const
        {
            return m_pmemo->base();
        }

    private:
        pmemo_t m_pmemo;
        typename memo_t::index_type m_index;

        bool is_in_table() const
        {
            return m_pmemo->is_in_table(m_index);
        }

    friend class boost::iterator_core_access;
        ref_t dereference() const
        {
            return m_pmemo->deref(m_index);
        }

        bool equal(memoize_iterator const& other) const
        {
            if (is_in_table() && other.is_in_table())
                return m_index == other.m_index;
            else if (!is_in_table() && !other.is_in_table())
                return base() == other.base();
            else
                return false;
        }

        void increment()
        {
            m_index = m_pmemo->next(m_index);
        }
    };


} // namespace memoized_detail


struct memo_table :
    private boost::noncopyable
{
    template< class V, class W >
    void detail_reset(V v, W w)
    {
        m_v = v; m_w = w;
    }

private:
    any_movable m_v, m_w;
};


struct op_make_memoized :
    callable<op_make_memoized>
{
    template< class Myself, class Range, class MemoTable = void >
    struct apply
    {
        typedef
            memoized_detail::memoize_iterator<
                typename range_iterator<Range>::type,
                boost::mpl::true_
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class Range >
    Result call(Range& rng, memo_table& tb) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

        typedef typename Result::iterator iter_t;
        typedef typename iter_t::memo_type memo_t;

        // They live outside of recursive cycles.
        std::auto_ptr<memo_t>
            pfirstData( new memo_t(boost::begin(rng)) ),
            plastData ( new memo_t(boost::end(rng))   );

        Result ret(iter_t(pfirstData.get()), iter_t(plastData.get()));
        tb.detail_reset(pfirstData, plastData);
        return ret;
    }

    template< class Myself, class Range >
    struct apply<Myself, Range>
    {
        typedef
            memoized_detail::memoize_iterator<
                typename range_iterator<Range>::type,
                boost::mpl::false_
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

        typedef typename Result::iterator iter_t;
        typedef typename iter_t::memo_type memo_t;

        boost::shared_ptr<memo_t>
            pfirstData( new memo_t(boost::begin(rng)) ),
            plastData ( new memo_t(boost::end(rng))   );

        return Result(iter_t(pfirstData), iter_t(plastData));
    }
};


PSTADE_CONSTANT(make_memoized, (op_make_memoized))
PSTADE_PIPABLE(memoized, (op_make_memoized))


} } // namespace pstade::oven


#endif
