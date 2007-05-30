#ifndef PSTADE_OVEN_DETAIL_IDENTITY_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_IDENTITY_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./prelude.hpp"
#include <boost/iterator/iterator_adaptor.hpp>
#include <pstade/copy_construct.hpp>
#include <pstade/is_convertible.hpp>
#include "../do_iter_swap.hpp"


namespace pstade { namespace oven { namespace detail {


template< class Iterator, class Traversal, class Difference >
struct identity_iterator;


template< class Iterator, class Traversal, class Difference >
struct identity_iterator_super
{
    typedef
        boost::iterator_adaptor<
            identity_iterator<Iterator, Traversal, Difference>,
            Iterator,
            boost::use_default,
            Traversal,
            boost::use_default,
            Difference
        >
    type;
};


template< class Iterator, class Traversal, class Difference >
struct identity_iterator :
    identity_iterator_super<Iterator, Traversal, Difference>::type
{
private:
    typedef typename identity_iterator_super<Iterator, Traversal, Difference>::type super_t;
    typedef typename super_t::difference_type diff_t;

public:
    explicit identity_iterator()
    { }

    explicit identity_iterator(Iterator it) :
        super_t(it)
    { }

    template< class I, class T, class D >
    identity_iterator(identity_iterator<I, T, D> const& other,
        typename boost::enable_if_convertible<I, Iterator>::type * = 0
    ) :
        super_t(other.base())
    { }

private:
friend class boost::iterator_core_access;
    template< class I, class T, class D >
    diff_t distance_to(identity_iterator<I, T, D> const& other) const
    {
        return pstade::copy_construct<diff_t>(other.base() - this->base());
    }
};


template< class I, class T, class D > inline
void iter_swap(identity_iterator<I, T, D> left, identity_iterator<I, T, D> right)
{
    do_iter_swap(left.base(), right.base());
}


} } } // namespace pstade::oven::detail


#endif
