#ifndef PSTADE_OVEN_CONST_LVALUES_HPP
#define PSTADE_OVEN_CONST_LVALUES_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp> // iterator_value
#include <boost/optional.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./detail/pure_traversal.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace const_lvalues_detail {


    template< class Iterator >
    struct const_lvalue_iterator;


    template< class Iterator >
    struct const_lvalue_iterator_super
    {
        typedef
            typename boost::iterator_value<Iterator>::type
        val_t;

        typedef
            boost::iterator_adaptor<
                const_lvalue_iterator<Iterator>,
                Iterator,
                val_t,
                typename detail::pure_traversal<Iterator>::type,
                val_t const&
            >
        type;
    };


    template< class Iterator >
    struct const_lvalue_iterator :
        const_lvalue_iterator_super<Iterator>::type
    {
    private:
        typedef typename const_lvalue_iterator_super<Iterator>::type super_t;
        typedef typename super_t::reference ref_t;
        typedef typename super_t::value_type val_t;

    public:
        explicit const_lvalue_iterator()
        { }

        explicit const_lvalue_iterator(Iterator const& it) :
            super_t(it)
        { }

        template< class I >
        const_lvalue_iterator(const_lvalue_iterator<I> const& other,
            typename boost::enable_if_convertible<I, Iterator>::type * = 0
        ) :
            super_t(other.base())
        { }

    private:
        mutable boost::optional<val_t> m_value;

    friend class boost::iterator_core_access;
        ref_t dereference() const
        {
            if (!m_value)
                m_value = *this->base();

            return *m_value;
        }

        void increment()
        {
            ++this->base_reference();
            m_value.reset();
        }

        void decrement()
        {
            --this->base_reference();
            m_value.reset();
        }

        template< class Difference >
        void advance(Difference const& d)
        {
            this->base_reference() += d;
            m_value.reset();
        }
    };


    template< class Range >
    struct baby
    {
        typedef
            const_lvalue_iterator<
                typename range_iterator<Range>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return result_type(rng);
        }
    };


} // namespace const_lvalues_detail


PSTADE_FUNCTION(make_const_lvalues, (const_lvalues_detail::baby<_>))
PSTADE_PIPABLE(const_lvalues, (op_make_const_lvalues))


} } // namespace pstade::oven


#endif
