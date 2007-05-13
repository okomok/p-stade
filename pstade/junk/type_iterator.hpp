#ifndef PSTADE_OVEN_TYPE_ITERATOR_HPP
#define PSTADE_OVEN_TYPE_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/optional.hpp>
#include <pstade/adl_barrier.hpp>
#include "./copy_range.hpp"


namespace pstade { namespace oven {


template< class Iterator >
struct type_iterator;


namespace type_iterator_detail {


    template< class Iterator, class Value >
    struct super_
    {
        typedef boost::iterator_adaptor<
            type_iterator<Iterator>,
            Iterator,
            Value
        > type;
    };


} // namespace type_iterator_detail


template< class Iterator, class Value >
struct type_iterator :
    type_iterator_detail::super_<Iterator>::type
{
private:
    typedef typename type_iterator_detail::super_<Iterator>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::difference_type diff_t;

public:
    type_iterator()
    { }

    explicit type_iterator(Iterator const& it) :
        super_t(it)
    { }

    template< class Iterator_ >
    type_iterator(
        type_iterator<Iterator_, Value> const& other,
        typename boost::enable_if_convertible<Iterator_, Iterator>::type * = 0
    ) :
        super_t(other.base())
    { }

private:
    boost::optional<Value> mutable m_cache;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        if (!m_cache)
            m_cache = oven::copy_range<Value>(*this->base());

        return *m_cache;
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

    void advance(diff_t d)
    {
        this->base_reference() += -d;
        m_cache.reset();
    }

    template< class Other >
    diff_t distance_to(Other const& other) const
    {
        return this->base() - other.base();
    }
};


template< class Value, class Iterator > inline
type_iterator<Iterator, Value> const
make_type_iterator(Iterator const& it)
{
    return type_iterator<Iterator, Value>(it);
}


} } // namespace pstade::oven


#endif
