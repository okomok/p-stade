#ifndef PSTADE_OVEN_DETAIL_TRANSFORM_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_TRANSFORM_ITERATOR_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Reason why 'boost::transform_iterator' rejected:
//
// IteratorCategory must be recomputed using 'detail::pure_traversal'.
// For example, consider 'rng|zipped|unzipped'.
// 'UnaryFun' may resurrect lvalue-ness of the base range,
// then a RandomAccess*Input* Iterator can turn into the RandomAccess.
// Though 'identities' can do the same thing, this will compile faster.


// Note:
//
// Consider the following simple functor.
//
// struct id
// {
//     typedef int const& result_type;
//     result_type operator()(int const& x) const
//     { return x; }
// };
//
// A transformed range whose 'reference' is 'int'(non-reference)
// cannot work with this functor because of dangling reference.
// A transformed range's 'reference' type is sometimes
// orthogonal to functor's 'result_type'.


// References:
//
// [1] Eric Niebler, transform_range, Boost.RangeEx, 2004.
// [2] David Abrahams, Jeremy Siek, Thomas Witt, transform_iterator, Boost.Iterator, 2003.


#include <boost/iterator/iterator_adaptor.hpp>
#include "../read.hpp"
#include "./pure_traversal.hpp"


namespace pstade { namespace oven { namespace detail {


template< class UnaryFun, class Iterator, class Reference, class Value >
struct transform_iterator;


template< class UnaryFun, class Iterator, class Reference, class Value >
struct transform_iterator_super
{
    typedef
        boost::iterator_adaptor<
            transform_iterator<UnaryFun, Iterator, Reference, Value>,
            Iterator,
            Value,
            typename pure_traversal<Iterator>::type,
            Reference
        >
    type;
};


template< class UnaryFun, class Iterator, class Reference, class Value >
struct transform_iterator :
    transform_iterator_super<UnaryFun, Iterator, Reference, Value>::type
{
private:
    typedef typename transform_iterator_super<UnaryFun, Iterator, Reference, Value>::type super_t;

public:
    transform_iterator()
    { }

    transform_iterator(Iterator it, UnaryFun fun) :
        super_t(it), m_fun(fun)
    { }

    template< class I, class R, class V >
    transform_iterator(transform_iterator<UnaryFun, I, R, V> const& other,
        typename boost::enable_if_convertible<I, Iterator>::type * = 0
    ) :
        super_t(other.base()), m_fun(other.function())
    { }

    UnaryFun function() const
    {
        return m_fun;
    }

    // boost compatible
    UnaryFun functor() const
    {
        return function();
    }

private:
    UnaryFun m_fun;

friend class boost::iterator_core_access;
    typename super_t::reference dereference() const
    {
        // 'read' seems not so bad idea. 
        return m_fun(read(this->base()));
    }
};


} } } // namespace pstade::oven::detail


#endif
