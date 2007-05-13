#ifndef PSTADE_OVEN_CONSTANT_ITERATOR_HPP
#define PSTADE_OVEN_CONSTANT_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Todo:
//
// Interoperatability (iterator_facade does nothing.)


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <pstade/object_generator.hpp>
#include "./detail/constant_reference.hpp"


namespace pstade { namespace oven {


template< class Iterator >
struct constant_iterator;


namespace constant_iterator_detail {


    template< class Iterator >
    struct super_
    {
        typedef
            boost::iterator_adaptor<
                constant_iterator<Iterator>,
                Iterator,
                boost::use_default,
                boost::use_default,
                typename detail::constant_reference<Iterator>::type
            >
        type;
    };


} // namespace constant_iterator_detail


template< class Iterator >
struct constant_iterator :
    constant_iterator_detail::super_<Iterator>::type
{
private:
    typedef typename constant_iterator_detail::super_<Iterator>::type super_t;

public:
    constant_iterator()
    { }

    constant_iterator(Iterator const& it) :
        super_t(it)
    { }

    template< class I >
    constant_iterator(constant_iterator<I> const& other,
        typename boost::enable_if_convertible<I, Iterator>::type * = 0
    ) :
        super_t(other.base())
    { }

friend class boost::iterator_core_access;
    // as is.
};


PSTADE_OBJECT_GENERATOR(make_constant_iterator,
    (constant_iterator< deduce<_1, to_value> >) const)


} } // namespace pstade::oven


#endif
