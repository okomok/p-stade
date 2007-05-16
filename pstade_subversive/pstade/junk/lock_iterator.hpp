#ifndef PSTADE_OVEN_LOCK_ITERATOR_HPP
#define PSTADE_OVEN_LOCK_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iterator> // advance, distance
#include <stdexcept> // range_error
#include <string>
#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/throw_exception.hpp>


namespace pstade { namespace oven {


template< class Iterator >
struct lock_iterator;


namespace lock_iterator_detail {


    template< class Reference >
    struct reference_proxy
    {
        reference_proxy(Reference ref) : m_ref(ref) {}

        Reference operator=(Value const& val)
        {
            m_ref = val
        }

        const T* operator->() const { return &m_value; }
        operator const T*() const { return &m_value; }
        Reference m_ref;
    };


    template< class Iterator >
    struct super_
    {
        typedef typename boost::iterator_reference<Iterator>::type ref_t;

        typedef boost::iterator_adaptor<
            lock_iterator<Iterator>,
            Iterator,
            boost::use_default,
            boost::use_default, // strictly speaking, non-conforming
            reference_proxy<ref_t>
        > type;
    };


} // namespace lock_iterator_detail


template< class Iterator >
struct lock_iterator :
    lock_iterator_detail::super_<Iterator>::type
{
private:
    typedef lock_iterator self_t;
    typedef typename lock_iterator_detail::super_<Iterator>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::difference_type diff_t;

public:
    lock_iterator() :
        m_singular(true)
    { }

    lock_iterator(Iterator it, Iterator first, Iterator last) :
        super_t(it),
        m_first(first), m_last(last),
        m_singular(false)
    { }

    template< class Iterator_ >
    lock_iterator(
        lock_iterator<Iterator_> other,
        typename boost::enable_if_convertible<Iterator_, Iterator>::type * = 0
    ) :
        super_t(other.base()),
        m_first(other.begin()), m_last(other.end()),
        m_singular(other.is_singular())
    {
        lock_iterator_detail::lock_singularity(other);
    }

    Iterator begin() const
    {
        lock_iterator_detail::lock_singularity(*this);
        return m_first;
    }

    Iterator end() const
    {
        lock_iterator_detail::lock_singularity(*this);
        return m_last;
    }

    bool is_begin() const
    {
        lock_iterator_detail::lock_singularity(*this);
        return this->base() == m_first;
    }

    bool is_end() const
    {
        lock_iterator_detail::lock_singularity(*this);
        return this->base() == m_last;
    }

    bool is_singular() const
    {
        return m_singular;
    }

private:
    Iterator m_first, m_last;
    bool m_singular;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        lock_iterator_detail::lock_singularity(*this);

        if (is_end())
            lock_iterator_detail::throw_error();

        return *this->base();
    }

    void increment()
    {
        lock_iterator_detail::lock_singularity(*this);

        if (is_end())
            lock_iterator_detail::throw_error();

        ++this->base_reference();
    }

    void decrement()
    {
        lock_iterator_detail::lock_singularity(*this);

        if (is_begin())
            lock_iterator_detail::throw_error();

        --this->base_reference();
    }

    void advance(diff_t d)
    {
        lock_iterator_detail::lock_singularity(*this);

        if (
            (d >= 0 && d > std::distance(this->base(), m_last)) ||
            (d < 0 && -d > std::distance(m_first, this->base()))
        ) {
            lock_iterator_detail::throw_error();
        }

        std::advance(this->base_reference(), d);
    }

    diff_t distance_to(self_t other) const
    {
        lock_iterator_detail::lock_singularity(*this);
        lock_iterator_detail::lock_singularity(other);

        return std::distance(this->base(), other.base());
    }
};


template< class Iterator > inline
lock_iterator<Iterator> const
make_lock_iterator(Iterator it, Iterator first, Iterator last)
{
    return lock_iterator<Iterator>(it, first, last);
}


} } // namespace pstade::oven


#endif
