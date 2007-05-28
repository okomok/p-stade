#ifndef PSTADE_OVEN_TAKEN_HPP
#define PSTADE_OVEN_TAKEN_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This could return RandomAccess, but can't return Bidirectional.
// Also, this can't be implemented using 'taken_while',
// because it requires the base range to be Readable or Lvalue.


#include "./detail/prelude.hpp"
#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./detail/minimum_pure.hpp"
#include "./do_iter_swap.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace taken_detail {


    template< class Iterator >
    struct take_iterator;


    template< class Iterator >
    struct take_iterator_super
    {
        typedef
            boost::iterator_adaptor<
                take_iterator<Iterator>,
                Iterator,
                boost::use_default,
                typename detail::minimum_pure<
                    boost::forward_traversal_tag,
                    typename boost::iterator_traversal<Iterator>::type
                >::type
            >
        type;
    };


    template< class Iterator >
    struct take_iterator :
        take_iterator_super<Iterator>::type
    {
    private:
        typedef typename take_iterator_super<Iterator>::type super_t;
        typedef typename super_t::reference ref_t;
        typedef typename super_t::difference_type diff_t;

    public:
        take_iterator()
        { }

        take_iterator(Iterator it, Iterator last, diff_t count) :
            super_t(it), m_last(last), m_count(count)
        {
            countdown();
        }

        template< class I >
        take_iterator(take_iterator<I> const& other,
            typename boost::enable_if_convertible<I, Iterator>::type * = 0
        ) :
            super_t(other.base()), m_last(other.end()), m_count(other.left_count())
        { }

        Iterator end() const
        {
            return m_last;
        }

        diff_t left_count() const
        {
            return m_count;
        }

    private:
        Iterator m_last;
        diff_t m_count;

        template< class Other >
        bool is_compatible(Other const& other) const
        {
            return m_last == other.end();
        }

        bool is_end() const
        {
            return this->base() == m_last;
        }

        void countdown()
        {
            if (is_end())
                return;

            if (m_count == 0)
                this->base_reference() = m_last;
            else
                --m_count;
        }

    friend class boost::iterator_core_access;
        ref_t dereference() const
        {
            BOOST_ASSERT(!is_end());
            return *this->base();
        }

        template< class I >
        bool equal(take_iterator<I> const& other) const
        {
            BOOST_ASSERT(is_compatible(other));
            return this->base() == other.base();
        }

        void increment()
        {
            BOOST_ASSERT(!is_end());
            ++this->base_reference();
            countdown();
        }
    };


    template< class I > inline
    void iter_swap(take_iterator<I> const& left, take_iterator<I> const& right)
    {
        do_iter_swap(left.base(), right.base());
    }


    template< class Range >
    struct baby
    {
        typedef typename
            range_difference<Range>::type
        diff_t;

        typedef
            take_iterator<
                typename range_iterator<Range>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng, diff_t n) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            BOOST_ASSERT(0 <= n);

            return result_type(
                iter_t(boost::begin(rng), boost::end(rng), n),
                iter_t(boost::end(rng),   boost::end(rng), n)
            );
        }
    };


} // namespace taken_detail


PSTADE_FUNCTION(make_taken, (taken_detail::baby<_>))
PSTADE_PIPABLE(taken, (op_make_taken))


} } // namespace pstade::oven


#endif
