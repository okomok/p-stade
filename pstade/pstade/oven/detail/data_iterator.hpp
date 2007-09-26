#ifndef PSTADE_OVEN_DETAIL_DATA_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_DATA_ITERATOR_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/optional/optional.hpp>
#include <boost/type_traits/is_same.hpp>
#include "../do_iter_swap.hpp"


namespace pstade { namespace oven { namespace detail {


template< class Iterator, class Data >
struct data_iterator;


template< class Iterator, class Data >
struct data_iterator_super
{
    typedef
        boost::iterator_adaptor<
            data_iterator<Iterator, Data>,
            Iterator
        >
    type;
};


template< class Iterator, class Data >
struct data_iterator :
    data_iterator_super<Iterator, Data>::type
{
private:
    typedef typename data_iterator_super<Iterator, Data>::type super_t;

public:
    typedef Data data_type;

    data_iterator()
    { }

    data_iterator(Iterator it, Data dt) :
        super_t(it), m_odt(dt)
    { }

    template< class I, class D >
    data_iterator(data_iterator<I, D> const& other,
        typename boost::enable_if_convertible<I, Iterator>::type * = 0,
        typename boost::enable_if_convertible<D, Data>::type * = 0
    ) :
        super_t(other.base())
    { }

    Data data() const
    {
        BOOST_ASSERT(m_odt);
        return *m_odt;
    }

private:
    boost::optional<Data> m_odt;

friend class boost::iterator_core_access;
    // as is.
};


template< class I1, class D1, class I2, class D2 > inline
void iter_swap(data_iterator<I1, D1> it1, data_iterator<I2, D2> it2, int = 0)
{
    do_iter_swap(it1.base(), it2.base());
}


template< class X >
struct is_data_iterator :
    boost::mpl::false_
{ };

template< class I, class V >
struct is_data_iterator< data_iterator<I, V> > :
    boost::mpl::true_
{ };


template< class VarIter, class Data >
struct has_data_aux :
    boost::is_same<typename VarIter::data_type, Data>
{ };

template< class X, class Data >
struct has_data :
    boost::mpl::and_<
        is_data_iterator<X>,
        has_data_aux<X, Data>
    >
{ };


} } } // namespace pstade::oven::detail


#endif
