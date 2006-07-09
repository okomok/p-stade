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
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp> // bidirectional_traversal_tag
#include <boost/throw_exception.hpp>
#include "./detail/an_iterator.hpp"
#include "./detail/minimum_traversal_type.hpp"


namespace pstade { namespace oven {


template< class Iterator >
struct lock_iterator;


struct lock_error :
    std::range_error
{
    explicit lock_error(std::string msg) :
        std::range_error(msg)
    { }
};


namespace lock_iterator_detail {


    template< class Iterator >
    struct traversal
    {
        typedef detail::an_iterator<boost::bidirectional_traversal_tag> biter_t;
        typedef boost::tuples::tuple<Iterator, biter_t> iters_t;
        typedef typename detail::minimum_traversal<iters_t>::type type;
    };


    template< class Iterator >
    struct super_
    {
        typedef boost::iterator_adaptor<
            lock_iterator<Iterator>,
            Iterator
        > type;
    };


    inline
    void throw_error()
    {
        lock_error err("out of 'lock_iterator' range");
        boost::throw_exception(err);
    }


    template< class Iterator >
    void lock_singularity(lock_iterator<Iterator> it)
    {
        if (it.is_singular()) {
            lock_error err("operation on default-constructed 'lock_iterator'");
            boost::throw_exception(err);
        }
    }


} // namespace lock_iterator_detail


template< class Iterator >
struct lock_iterator_impl :
    lock_iterator_detail::impl_super<Iterator>::type
{
private:
    typedef lock_iterator self_t;
    typedef typename lock_iterator_detail::super_<Iterator>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::difference_type diff_t;

public:
    lock_iterator()
    { }

    lock_iterator(Iterator it, boost::mutex& mtx) :
        super_t(it), m_pmtx(boost::addressof(mtx))
    { }

    template< class Iterator_ >
    lock_iterator(
        lock_iterator<Iterator_> other,
        typename boost::enable_if_convertible<Iterator_, Iterator>::type * = 0
    ) :
        super_t(other.base()), m_pmtx(other.m_pmtx)
    { }

private:
    Iterator m_first, m_last;
    bool m_singular;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        lock_iterator_detail::lock_singularity(*this);

        if (is_end())
            lock_iterator_detail::throw_error();

        return *this->base_reference();
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
