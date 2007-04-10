#ifndef PSTADE_OVEN_REVERSED_HPP
#define PSTADE_OVEN_REVERSED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/next_prior.hpp> // prior
#include <boost/optional.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace reversed_detail {


    // This replaces 'boost::reverse_iterator' for
    // http://std.dkuug.dk/jtc1/sc22/wg21/docs/lwg-defects.html#198


    template< class BidiIter >
    struct reverse_iterator;


    template< class BidiIter >
    struct reverse_iterator_super
    {
        typedef
            boost::iterator_adaptor<
                reverse_iterator<BidiIter>,
                BidiIter
            >
        type;
    };


    template< class BidiIter >
    struct reverse_iterator :
        reverse_iterator_super<BidiIter>::type
    {
    private:
        typedef typename reverse_iterator_super<BidiIter>::type super_t;
        typedef typename super_t::reference ref_t;
        typedef typename super_t::difference_type diff_t;

    public:
        explicit reverse_iterator()
        { }

        explicit reverse_iterator(BidiIter const& it) :
            super_t(it)
        { }

        template< class B >
        reverse_iterator(reverse_iterator<B> const& other,
            typename boost::enable_if_convertible<B, BidiIter>::type * = 0
        ) :
            super_t(other.base())
        { }

    private:
        mutable boost::optional<BidiIter> m_cache;

    friend class boost::iterator_core_access;
        ref_t dereference() const
        {
            if (!m_cache)
                m_cache = boost::prior(this->base());

            return **m_cache;
        }

        void increment()
        {
            --this->base_reference();
            m_cache.reset();
        }

        void decrement()
        {
            ++this->base_reference();
            m_cache.reset();
        }

        void advance(diff_t const& d)
        {
            this->base_reference() += -d;
            m_cache.reset();
        }

        template< class B >
        diff_t distance_to(reverse_iterator<B> const& other) const
        {
            return this->base() - other.base();
        }
    };


    template< class Range >
    struct baby
    {
        typedef
            reverse_iterator<
                typename range_iterator<Range>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
            return result_type(boost::end(rng), boost::begin(rng)); // take care of the order!
        }
    };


} // namespace reversed_detail


PSTADE_FUNCTION(make_reversed, (reversed_detail::baby<_>))
PSTADE_PIPABLE(reversed, (op_make_reversed))


// This seems too primitive to hide.
using reversed_detail::reverse_iterator;


} } // namespace pstade::oven


#endif
