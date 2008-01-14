#ifndef PSTADE_OVEN_DETAIL_POP_ITERATOR_OF_FORWARD_HPP
#define PSTADE_OVEN_DETAIL_POP_ITERATOR_OF_FORWARD_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/next_prior.hpp>
#include "../do_iter_swap.hpp"


namespace pstade { namespace oven { namespace detail {


template< class ForwardIter >
struct pop_iterator_of_forward;


template< class ForwardIter >
struct pop_iterator_of_forward_super
{
    typedef
        boost::iterator_adaptor<
            pop_iterator_of_forward<ForwardIter>,
            ForwardIter
        >
    type;
};


template< class ForwardIter >
struct pop_iterator_of_forward :
    pop_iterator_of_forward_super<ForwardIter>::type
{
private:
    typedef typename pop_iterator_of_forward_super<ForwardIter>::type super_t;

public:
    explicit pop_iterator_of_forward()
    { }

    explicit pop_iterator_of_forward(ForwardIter it, ForwardIter last) :
        super_t(it), m_last(last)
    {
        look_next();
    }

    explicit pop_iterator_of_forward(ForwardIter last) : // the end iterator
        super_t(last), m_last(last)
    { }

    template< class F >
    pop_iterator_of_forward(pop_iterator_of_forward<F> const& other,
        typename boost::enable_if_convertible<F, ForwardIter>::type * = 0
    ) :
        super_t(other.base()), m_last(other.end())
    { }

    ForwardIter end() const
    {
        return m_last;
    }

private:
    ForwardIter m_last;

    void look_next()
    {            
        BOOST_ASSERT(this->base() != m_last);

        if (boost::next(this->base()) == m_last)
            this->base_reference() = m_last;
    }

friend class boost::iterator_core_access;
    void increment()
    {
        ++this->base_reference();
        look_next();
    }
};


template< class F1, class F2 > inline
void iter_swap(pop_iterator_of_forward<F1> it1, pop_iterator_of_forward<F2> it2, int = 0)
{
    do_iter_swap(it1.base(), it2.base());
}


} } } // namespace pstade::oven::detail


#endif
