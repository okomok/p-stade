#ifndef PSTADE_OVEN_CHECK_ITERATOR_HPP
#define PSTADE_OVEN_CHECK_ITERATOR_HPP


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
struct check_iterator;


struct check_error :
    std::range_error
{
    explicit check_error(std::string msg) :
        std::range_error(msg)
    { }
};


namespace check_iterator_detail {


    template< class Iterator >
    struct super_
    {
        typedef boost::iterator_adaptor<
            check_iterator<Iterator>,
            Iterator
        > type;
    };


    inline
    void throw_error()
    {
        check_error err("out of 'check_iterator' range");
        boost::throw_exception(err);
    }


    template< class Iterator >
    void check_singularity(check_iterator<Iterator> it)
    {
        if (it.is_singular()) {
            check_error err("operation on default-constructed 'check_iterator'");
            boost::throw_exception(err);
        }
    }


} // namespace check_iterator_detail


template< class Iterator >
struct check_iterator :
    check_iterator_detail::super_<Iterator>::type
{
private:
    typedef check_iterator self_t;
    typedef typename check_iterator_detail::super_<Iterator>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::difference_type diff_t;

public:
    check_iterator() :
        m_singular(true)
    { }

    check_iterator(Iterator it, Iterator first, Iterator last) :
        super_t(it),
        m_first(first), m_last(last),
        m_singular(false)
    { }

    template< class Iterator_ >
    check_iterator(
        check_iterator<Iterator_> other,
        typename boost::enable_if_convertible<Iterator_, Iterator>::type * = 0
    ) :
        super_t(other.base()),
        m_first(other.begin()), m_last(other.end()),
        m_singular(other.is_singular())
    {
        check_iterator_detail::check_singularity(other);
    }

    Iterator begin() const
    {
        check_iterator_detail::check_singularity(*this);
        return m_first;
    }

    Iterator end() const
    {
        check_iterator_detail::check_singularity(*this);
        return m_last;
    }

    bool is_begin() const
    {
        check_iterator_detail::check_singularity(*this);
        return this->base() == m_first;
    }

    bool is_end() const
    {
        check_iterator_detail::check_singularity(*this);
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
        check_iterator_detail::check_singularity(*this);

        if (is_end())
            check_iterator_detail::throw_error();

        return *this->base();
    }

    void increment()
    {
        check_iterator_detail::check_singularity(*this);

        if (is_end())
            check_iterator_detail::throw_error();

        ++this->base_reference();
    }

    void decrement()
    {
        check_iterator_detail::check_singularity(*this);

        if (is_begin())
            check_iterator_detail::throw_error();

        --this->base_reference();
    }

    void advance(diff_t d)
    {
        check_iterator_detail::check_singularity(*this);

        if (
            (d >= 0 && d > std::distance(this->base(), m_last)) ||
            (d < 0 && -d > std::distance(m_first, this->base()))
        ) {
            check_iterator_detail::throw_error();
        }

        std::advance(this->base_reference(), d);
    }

    diff_t distance_to(self_t other) const
    {
        check_iterator_detail::check_singularity(*this);
        check_iterator_detail::check_singularity(other);

        return std::distance(this->base(), other.base());
    }
};


template< class Iterator > inline
check_iterator<Iterator> const
make_check_iterator(Iterator it, Iterator first, Iterator last)
{
    return check_iterator<Iterator>(it, first, last);
}


} } // namespace pstade::oven


#endif
