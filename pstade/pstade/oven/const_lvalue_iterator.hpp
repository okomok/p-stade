#ifndef PSTADE_OVEN_CONST_LVALUE_ITERATOR_HPP
#define PSTADE_OVEN_CONST_LVALUE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp> // iterator_value
#include <boost/optional.hpp>
#include <pstade/object_generator.hpp>
#include "./detail/pure_traversal.hpp"


namespace pstade { namespace oven {


template< class Iterator >
struct const_lvalue_iterator;


namespace const_lvalue_iterator_detail {


    template< class Iterator >
    struct super_
    {
        typedef typename boost::iterator_value<Iterator>::type val_t;

        typedef boost::iterator_adaptor<
            const_lvalue_iterator<Iterator>,
            Iterator,
            val_t,
            typename detail::pure_traversal<Iterator>::type, // *pure* makes 'facade_iterator_category' recompute.
            val_t const&
        > type;
    };


} // namespace const_lvalue_iterator_detail


template< class Iterator >
struct const_lvalue_iterator :
    const_lvalue_iterator_detail::super_<Iterator>::type
{
private:
    typedef typename const_lvalue_iterator_detail::super_<Iterator>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::value_type val_t;

public:
    explicit const_lvalue_iterator()
    { }

    explicit const_lvalue_iterator(Iterator const& it) :
        super_t(it)
    { }

    template< class Iterator_ >
    const_lvalue_iterator(
        const_lvalue_iterator<Iterator_> const& other,
        typename boost::enable_if_convertible<Iterator_, Iterator>::type * = 0
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


PSTADE_OBJECT_GENERATOR(make_const_lvalue_iterator,
    (const_lvalue_iterator< deduce<_1, to_value> >) const)


} } // namespace pstade::oven


#endif
