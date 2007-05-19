#ifndef PSTADE_OVEN_POPPED_HPP
#define PSTADE_OVEN_POPPED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This never accepts an empty range,
// following Container and Haskell's 'init'.


#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/next_prior.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./do_iter_swap.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./range_traversal.hpp"


namespace pstade { namespace oven {


namespace popped_detail {


    template< class ForwardIter >
    struct pop_iterator;


    template< class ForwardIter >
    struct pop_iterator_super
    {
        typedef
            boost::iterator_adaptor<
                pop_iterator<ForwardIter>,
                ForwardIter
            >
        type;
    };


    template< class ForwardIter >
    struct pop_iterator :
        pop_iterator_super<ForwardIter>::type
    {
    private:
        typedef typename pop_iterator_super<ForwardIter>::type super_t;

    public:
        explicit pop_iterator()
        { }

        explicit pop_iterator(ForwardIter it, ForwardIter last) :
            super_t(it), m_last(last)
        {
            look_next();
        }

        explicit pop_iterator(ForwardIter last) : // the end iterator
            super_t(last), m_last(last)
        { }

        template< class F >
        pop_iterator(pop_iterator<F> const& other,
            typename boost::enable_if_convertible<F, ForwardIter>::type * = 0
        ) :
            super_t(other.base()), m_last(other.end())
        { }

        ForwardIter end() const
        {
            return m_last;
        }

    private:
        ForwardIter m_last;

        void look_next()
        {            
            BOOST_ASSERT(this->base() != m_last);

            if (boost::next(this->base()) == m_last)
                this->base_reference() = m_last;
        }

    friend class boost::iterator_core_access;
        void increment()
        {
            ++this->base_reference();
            look_next();
        }
    };


    template< class F > inline
    void iter_swap(pop_iterator<F> const& left, pop_iterator<F> const& right)
    {
        do_iter_swap(left.base(), right.base());
    }


    template< class Range >
    struct baby
    {
        typedef typename
            boost::mpl::eval_if<
                is_convertible<
                    typename range_traversal<Range>::type, boost::bidirectional_traversal_tag
                >,
                iter_range_of<Range>,
                iter_range< pop_iterator<typename range_iterator<Range>::type> >
            >::type const
        result_type;

        result_type operator()(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            BOOST_ASSERT(!boost::empty(rng));
            return aux(boost::begin(rng), boost::end(rng), typename range_traversal<Range>::type());
        }

        template< class Iterator >
        result_type aux(Iterator first, Iterator last, boost::bidirectional_traversal_tag) const
        {
            PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
            return result_type(first, boost::prior(last));
        }

        template< class Iterator >
        result_type aux(Iterator first, Iterator last, boost::forward_traversal_tag) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            typedef typename result_type::iterator iter_t;
            return result_type(iter_t(first, last), iter_t(last));
        }
    };


} // namespace popped_detail


PSTADE_FUNCTION(make_popped, (popped_detail::baby<_>))
PSTADE_PIPABLE(popped, (op_make_popped))


} } // namespace pstade::oven


#endif
