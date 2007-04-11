#ifndef PSTADE_OVEN_MEMOIZED_HPP
#define PSTADE_OVEN_MEMOIZED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Modeled after: <boost/spirit/iterator/multi_pass.hpp>
//
/*=============================================================================
    Copyright (c) 2001, Daniel C. Nuffer
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
//
// Differences:
//   No unique-check; rarely unique in range.
//   No end-iterator-check; it seems redundant.


#include <deque>
#include <memory> // auto_ptr
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
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

        explicit memo(Iterator const& it) :
            m_base(it)
        { }

        bool is_in_table(index_type const& i) const
        {
            return i != m_table.size();
        }

        value_t const& table(index_type const& i) const
        {
            return m_table[i];
        }

        Iterator const& base() const
        {
            return m_base;
        }

        void increment()
        {
            m_table.push_back(dereference());
            ++m_base;
            m_ovalue.reset();
        }

        value_t const& dereference()
        {
            if (!this->m_ovalue)
                this->m_ovalue = *m_base;

            return *this->m_ovalue;
        }

    private:
        Iterator m_base;
        boost::optional<value_t> m_ovalue; // shared to boost the speed!
        table_t m_table;
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


    template< class Iterator, class IsRecursive = boost::mpl::false_ >
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

        Iterator const& base() const
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
            if (is_in_table())
                return m_pmemo->table(m_index);
            else
                return m_pmemo->dereference();
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
            if (is_in_table()) {
                ++m_index;
            }
            else {
                m_pmemo->increment();
                ++m_index;
            }
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
                boost::mpl::true_ // recursive
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
                typename range_iterator<Range>::type
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
