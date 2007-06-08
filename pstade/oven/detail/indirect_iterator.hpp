#ifndef PSTADE_OVEN_DETAIL_INDIRECT_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_INDIRECT_ITERATOR_HPP
#include "../prelude.hpp"


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


#include <boost/indirect_reference.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/pointee.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/use_default.hpp>
#include "../do_iter_swap.hpp"
#include "../read.hpp"
#include "./pure_traversal.hpp"


namespace pstade { namespace oven { namespace detail {


template< class Iterator, class Value, class Category, class Reference, class Difference >
struct indirect_iterator;


template< class Iterator, class Value, class Category, class Reference, class Difference >
struct indirect_iterator_super
{
    typedef typename
        boost::iterator_value<Iterator>::type
    base_val_t;

    typedef typename
        eval_if_use_default< Value, boost::pointee<base_val_t> >::type
    val_t;

    // lvalue-ness resurrection
    typedef typename
        eval_if_use_default< Category, pure_traversal<Iterator> >::type
    trv_t;

    typedef typename
        eval_if_use_default<
            Reference,
            boost::mpl::eval_if< boost::is_same<Value, boost::use_default>,
                boost::indirect_reference<base_val_t>,
                boost::add_reference<Value>
            >
        >::type
    ref_t;

    typedef
        boost::iterator_adaptor<
            indirect_iterator<Iterator, Value, Category, Reference, Difference>,
            Iterator,
            val_t,
            trv_t,
            ref_t,
            Difference
        >
    type;
};


template<
    class Iterator,
    class Value      = boost::use_default,
    class Category   = boost::use_default,
    class Reference  = boost::use_default,
    class Difference = boost::use_default
>
struct indirect_iterator :
    indirect_iterator_super<Iterator, Value, Category, Reference, Difference>::type
{
private:
    typedef typename indirect_iterator_super<Iterator, Value, Category, Reference, Difference>::type super_t;

public:
    explicit indirect_iterator()
    { }

    explicit indirect_iterator(Iterator it) :
        super_t(it)
    { }

    template< class I, class V, class C, class R, class D >
    indirect_iterator(indirect_iterator<I, V, C, R, D> const& other,
        typename boost::enable_if_convertible<I, Iterator>::type * = 0
    ) :
        super_t(other.base())
    { }

private:    
friend class boost::iterator_core_access;
    typename super_t::reference dereference() const
    {
        // '**this->base()' won't work in the case of proxy.
        return *read(this->base());
    }
};


template< class I1, class V1, class C1, class R1, class D1, class I2, class V2, class C2, class R2, class D2 > inline
void iter_swap(indirect_iterator<I1, V1, C1, R1, D1> it1, indirect_iterator<I2, V2, C2, R2, D2> it2, int = 0)
{
    do_iter_swap(read(it1.base()), read(it2.base()));
}


} } } // namespace pstade::oven::detail


#endif
