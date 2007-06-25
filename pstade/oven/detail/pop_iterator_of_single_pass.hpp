#ifndef PSTADE_OVEN_DETAIL_POP_ITERATOR_OF_SINGLE_PASS_HPP
#define PSTADE_OVEN_DETAIL_POP_ITERATOR_OF_SINGLE_PASS_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include "../read.hpp"
#include "./begin_end_tag.hpp"


namespace pstade { namespace oven { namespace detail {


template< class Iterator >
struct pop_iterator_of_single_pass;


template< class Iterator >
struct pop_iterator_of_single_pass_super
{
    typedef
        boost::iterator_adaptor<
            pop_iterator_of_single_pass<Iterator>,
            Iterator,
            boost::use_default,
            boost::use_default,
            typename boost::iterator_value<Iterator>::type
        >
    type;
};


template< class Iterator >
struct pop_iterator_of_single_pass :
    pop_iterator_of_single_pass_super<Iterator>::type
{
private:
    typedef typename pop_iterator_of_single_pass_super<Iterator>::type super_t;
    typedef typename super_t::value_type val_t;
    typedef typename super_t::reference ref_t;

public:
    pop_iterator_of_single_pass(Iterator it, begin_tag) :
        super_t(it)
    {
        increment();
    }

    pop_iterator_of_single_pass(Iterator it, end_tag) :
        super_t(it)
    { }

template< class > friend struct pop_iterator_of_single_pass;
    template< class I >
    pop_iterator_of_single_pass(pop_iterator_of_single_pass<I> const& other,
        typename boost::enable_if_convertible<I, Iterator>::type * = 0
    ) :
        super_t(other.base()), m_value(other.m_value)
    { }

private:
    val_t m_value;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        return m_value;
    }

    void increment()
    {
        m_value = read(this->base());
        ++this->base_reference();
    }
};


} } } // namespace pstade::oven::detail


#endif
