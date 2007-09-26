#ifndef PSTADE_OVEN_DETAIL_FILTER_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_FILTER_ITERATOR_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// (C) Copyright David Abrahams 2002.
// (C) Copyright Jeremy Siek    2002.
// (C) Copyright Thomas Witt    2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include "../do_iter_swap.hpp"
#include "../read.hpp"
#include "./minimum_pure.hpp"


namespace pstade { namespace oven { namespace detail {


template< class Predicate, class Iterator >
struct filter_iterator;


template< class Predicate, class Iterator >
struct filter_iterator_super
{
    typedef
        boost::iterator_adaptor<
            filter_iterator<Predicate, Iterator>,
            Iterator,
            boost::use_default,
            typename minimum_pure<
                boost::bidirectional_traversal_tag,
                typename boost::iterator_traversal<Iterator>::type
            >::type
        >
    type;
};


template< class Predicate, class Iterator >
struct filter_iterator :
    filter_iterator_super<Predicate, Iterator>::type
{
private:
    typedef typename filter_iterator_super<Predicate, Iterator>::type super_t;

public:
    typedef Predicate predicate_type;

    filter_iterator()
    { }

    filter_iterator(Predicate pred, Iterator it, Iterator last) :
        super_t(it), m_pred(pred), m_last(last)
    {
        satisfy_predicate();
    }

    template< class I >
    filter_iterator(filter_iterator<Predicate, I> const& other,
        typename boost::enable_if_convertible<I, Iterator>::type * = 0
    ) :
        super_t(other.base()), m_pred(other.predicate()), m_last(other.end())
    { }

    Predicate predicate() const
    {
        return m_pred;
    }

    Iterator end() const
    {
        return m_last;
    }

private:
    Predicate m_pred;
    Iterator m_last;

    void satisfy_predicate()
    {
        while ( this->base() != m_last && !m_pred(read(this->base())) )
            ++(this->base_reference());
    }

friend class boost::iterator_core_access;
    void increment()
    {
        ++this->base_reference();
        satisfy_predicate();
    }

    void decrement()
    {
        while ( !m_pred(read(--(this->base_reference()))) )
            ;
    }
};


template< class P1, class I1, class P2, class I2 > inline
void iter_swap(filter_iterator<P1, I1> it1, filter_iterator<P2, I2> it2, int = 0)
{
    do_iter_swap(it1.base(), it2.base());
}


} } } // namespace pstade::oven::detail


#endif
