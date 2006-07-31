#ifndef PSTADE_OVEN_CONST_LVALUE_ITERATOR_HPP
#define PSTADE_OVEN_CONST_LVALUE_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp> // iterator_value
#include <boost/optional.hpp>


namespace pstade { namespace oven {


template< class Iterator >
struct const_lvalue_iterator;


namespace const_lvalue_iterator_detail {


    template< class Iterator >
    struct traversal :
        boost::detail::pure_traversal_tag< // makes 'facade_iterator_category' recompute.
            typename boost::iterator_traversal<Iterator>::type
        >
    { };


    template< class Iterator >
    struct super_
    {
        typedef typename boost::iterator_value<Iterator>::type val_t;

        typedef boost::iterator_adaptor<
            const_lvalue_iterator<Iterator>,
            Iterator,
            val_t,
            typename traversal<Iterator>::type,
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
    typedef typename super_t::difference_type diff_t;

public:
    const_lvalue_iterator()
    { }

    explicit const_lvalue_iterator(Iterator const& it) :
        super_t(it)
    { }

template< class > friend struct const_lvalue_iterator;
    template< class Iterator_ >
    const_lvalue_iterator(
        const_lvalue_iterator<Iterator_> const& other,
        typename boost::enable_if_convertible<Iterator_, Iterator>::type * = 0
    ) :
        super_t(other.base()), m_value(other.m_value)
    { }

private:
    boost::optional<val_t> mutable m_value;

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

    void advance(diff_t d)
    {
        this->base_reference() += d;
        m_value.reset();
    }

    template< class Other >
    diff_t distance_to(Other const& other) const
    {
        return other.base() - this->base();
    }
};


template< class Iterator > inline
const_lvalue_iterator<Iterator> const
make_const_lvalue_iterator(Iterator const& it)
{
    return const_lvalue_iterator<Iterator>(it);
}


} } // namespace pstade::oven


#endif
