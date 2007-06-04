#ifndef PSTADE_OVEN_TEST_PROXY_ITERATOR_HPP
#define PSTADE_OVEN_TEST_PROXY_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/detail/prelude.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_traits.hpp> // iterator_value
#include <pstade/oven/do_iter_swap.hpp>
#include <pstade/oven/read.hpp>
#include <pstade/oven/write.hpp>


namespace pstade { namespace oven { namespace test {


template< class Iterator >
struct proxy
{
    typedef typename boost::iterator_value<Iterator>::type value_t;

    operator value_t() const
    {
        return read(m_it);
    }

    void operator=(value_t const& v) const
    {
        write(m_it, v);
    }

#if !defined(PSTADE_OVEN_TEST_DO_ITER_SWAP)
    // just in case '*left = *right'.
    void operator=(proxy const& other) const
    {
        write(m_it, read(other.m_it));
    }
#endif

    explicit proxy(Iterator it) :
        m_it(it)
    { }

private:
    Iterator m_it;
};


template< class Iterator >
struct proxy_iterator;


template< class Iterator >
struct proxy_iterator_super
{
    typedef
        boost::iterator_adaptor<
            proxy_iterator<Iterator>,
            Iterator,
            typename boost::iterator_value<Iterator>::type,
            boost::use_default,
            proxy<Iterator>
        >
    type;
};


template< class Iterator >
struct proxy_iterator :
    proxy_iterator_super<Iterator>::type
{
private:
    typedef typename proxy_iterator_super<Iterator>::type super_t;
    typedef typename super_t::reference ref_t;

public:
    explicit proxy_iterator()
    { }

    explicit proxy_iterator(Iterator it) :
        super_t(it)
    { }

    template< class I >
    proxy_iterator(proxy_iterator<I> const& other,
        typename boost::enable_if_convertible<I, Iterator>::type * = 0
    ) :
        super_t(other.base())
    { }

private:
friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        return ref_t(this->base());
    }
};


#if 0 // intentionally disabled

template< class I1, class I2 > inline
void pstade_oven_iter_swap(proxy_iterator<I1> it1, proxy_iterator<I2> it2)
{
    do_iter_swap(it1.base(), it2.base());
}

#endif


} } } // namespace pstade::oven::test


#endif
