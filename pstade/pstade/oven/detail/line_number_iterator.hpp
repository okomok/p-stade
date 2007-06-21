#ifndef PSTADE_OVEN_DETAIL_LINE_NUMBER_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_LINE_NUMBER_ITERATOR_HPP
#include "../prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright Takeshi Mouri 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/mpl/bool.hpp>
#include "../do_iter_swap.hpp"
#include "./minimum_pure.hpp"


namespace pstade { namespace oven { namespace detail {


template< class Iterator >
struct line_number_iterator;


template< class Iterator >
struct line_number_iterator_super
{
    typedef
        boost::iterator_adaptor<
            line_number_iterator<Iterator>,
            Iterator,
            boost::use_default,
            typename minimum_pure<
                boost::forward_traversal_tag,
                typename boost::iterator_traversal<Iterator>::type
            >::type
        >
    type;
};


template< class Iterator >
struct line_number_iterator :
    line_number_iterator_super<Iterator>::type
{
private:
    typedef typename line_number_iterator_super<Iterator>::type super_t;
    typedef typename super_t::value_type val_t;

public:
    line_number_iterator()
    { }

    line_number_iterator(Iterator it, int n, val_t nl) :
        super_t(it), m_num(n), m_nl(nl)
    { }

    int line_number() const
    {
        return m_num;
    }

    val_t newline() const
    {
        return m_nl;
    }

private:
    int m_num;
    val_t m_nl;

friend class boost::iterator_core_access;
    void increment()
    {
        if (*this->base() == m_nl)
            ++m_num;

        ++this->base_reference();
    }
};


template< class I1, class I2 > inline
void iter_swap(line_number_iterator<I1> it1, line_number_iterator<I2> it2, int = 0)
{
    do_iter_swap(it1.base(), it2.base());
}


template< class X >
struct is_line_number_iterator :
    boost::mpl::false_
{ };

template< class I >
struct is_line_number_iterator< line_number_iterator<I> > :
    boost::mpl::true_
{ };


} } } // namespace pstade::oven::detail


#endif
