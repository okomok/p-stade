#ifndef PSTADE_OVEN_CHECK_ITERATOR_HPP
#define PSTADE_OVEN_CHECK_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>


namespace pstade { namespace oven {


template< class Iterator >
struct check_iterator;


namespace check_iterator_detail {


    template< class Iterator >
    struct super_
    {
        typedef boost::iterator_adaptor<
            check_iterator<Iterator>,
            Iterator
        > type;
    };


} // namespace check_iterator_detail


template< class Iterator >
struct check_iterator :
    check_iterator_detail::super_<Iterator>::type
{
private:
    typedef typename check_iterator_detail::super_<Iterator>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::difference_type diff_t;

public:
    check_iterator()
    { }

    check_iterator(Iterator it, Iterator first, Iterator last) :
        super_t(it), m_first(first), m_last(last)
    { }

    template< class Iterator_ >
    check_iterator(
        check_iterator<Iterator_> other,
        typename boost::enable_if_convertible<Iterator_, Iterator>::type * = 0
    ) :
        super_t(other.base()), m_first(other.begin()), m_last(other.end())
    { }

    Iterator begin() const
    { return m_first; }

    Iterator end() const
    { return m_last; }

    bool is_begin() const
    { return this->base() == m_first; }

    bool is_end() const
    { return this->base() == m_last; }

private:
    Iterator m_first, m_last;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT(!is_end());
        return *this->base_reference();
    }

    void increment()
    {
        BOOST_ASSERT(!is_end());
        ++this->base_reference();
    }

    void decrement()
    {
        BOOST_ASSERT(!is_begin());
        --this->base_reference();
    }

    void advance_to(diff_t d)
    {
        BOOST_ASSERT(m_first <= this->base() + d && this->base() + d <= m_last);
        this->base_reference() += d;
    }
};


template< class Iterator > inline const
check_iterator<Iterator>
make_check_iterator(Iterator it, Iterator first, Iterator last)
{
    return check_iterator<Iterator>(it, first, last);
}


} } // namespace pstade::oven


#endif
