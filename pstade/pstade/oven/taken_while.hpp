#ifndef PSTADE_OVEN_TAKEN_WHILE_HPP
#define PSTADE_OVEN_TAKEN_WHILE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] Robert Ramey, head_iterator, Boost.Serialization, 2002.
//     http://www.boost.org/libs/serialization/doc/dataflow.html
// [2] John Torjo and Matthew Wilson, break_iterator, Iterable Range Library, 2004.
//     http://www.torjo.com/rangelib/index.html


#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include <pstade/to_ref.hpp>
#include "./concepts.hpp"
#include "./detail/minimum_pure.hpp"
#include "./do_iter_swap.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace taken_while_detail {


    template< class Iterator, class Predicate >
    struct take_while_iterator;


    template< class Iterator, class Predicate >
    struct take_while_iterator_super
    {
        typedef
            boost::iterator_adaptor<
                take_while_iterator<Iterator, Predicate>,
                Iterator,
                boost::use_default,
                typename detail::minimum_pure<
                    boost::forward_traversal_tag,
                    typename boost::iterator_traversal<Iterator>::type
                >::type
            >
        type;
    };


    template< class Iterator, class Predicate >
    struct take_while_iterator :
        take_while_iterator_super<Iterator, Predicate>::type
    {
    private:
        typedef typename take_while_iterator_super<Iterator, Predicate>::type super_t;
        typedef typename super_t::reference ref_t;

    public:
        take_while_iterator()
        { }

        take_while_iterator(Iterator it, Iterator last, Predicate pred) :
            super_t(it), m_last(last), m_pred(pred)
        {
            check_predicate();
        }

        template< class I >
        take_while_iterator(take_while_iterator<I, Predicate> const& other,
            typename boost::enable_if_convertible<I, Iterator>::type * = 0
        ) :
            super_t(other.base()), m_last(other.end()), m_pred(other.predicate())
        { }

        Iterator end() const
        {
            return m_last;
        }

        Predicate predicate() const
        {
            return m_pred;
        }

    private:
        Iterator m_last;
        Predicate m_pred;

        template< class Other >
        bool is_compatible(Other const& other) const
        {
            return m_last == other.end();
        }

        bool is_end() const
        {
            return this->base() == m_last;
        }

        void check_predicate()
        {
            if (is_end())
                return;

            if (!m_pred( to_ref(*this->base()) ))
                this->base_reference() = m_last;
        }

    friend class boost::iterator_core_access;
        ref_t dereference() const
        {
            BOOST_ASSERT(!is_end());
            return *this->base();
        }

        template< class I >
        bool equal(take_while_iterator<I, Predicate> const& other) const
        {
            BOOST_ASSERT(is_compatible(other));
            return this->base() == other.base();
        }

        void increment()
        {
            BOOST_ASSERT(!is_end());
            ++this->base_reference();
            check_predicate();
        }
    };


    template< class I, class P > inline
    void iter_swap(take_while_iterator<I, P> const& left, take_while_iterator<I, P> const& right)
    {
        do_iter_swap(left.base(), right.base());
    }


    template< class Range, class Predicate >
    struct baby
    {
        typedef
            take_while_iterator<
                typename range_iterator<Range>::type,
                typename pass_by_value<Predicate>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng, Predicate& pred) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

            return result_type(
                iter_t(boost::begin(rng), boost::end(rng), pred),
                iter_t(boost::end(rng),   boost::end(rng), pred)
            );
        }
    };


} // namespace taken_while_detail


PSTADE_FUNCTION(make_taken_while, (taken_while_detail::baby<_, _>))
PSTADE_PIPABLE(taken_while, (op_make_taken_while))


} } // namespace pstade::oven


#endif
