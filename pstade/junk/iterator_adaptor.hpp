#ifndef PSTADE_OVEN_ITERATOR_ADAPTOR_HPP
#define PSTADE_OVEN_ITERATOR_ADAPTOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_adaptor.hpp>


namespace pstade { namespace oven {


namespace iterator_adaptor_detail {


    template<
        class Derived,
        class Base,
        class Value,
        class Traversal,
        class Reference,
        class Difference
    >
    struct super_
    {
        typedef boost::iterator_adaptor<
            Derived, Base, Value, Traversal, Reference, Difference
        > type;
    };


} // namespace iterator_adaptor_detail

template<
    class Derived,
    class Base,
    class Value      = boost::use_default,
    class Traversal  = boost::use_default,
    class Reference  = boost::use_default,
    class Difference = boost::use_default
>
struct iterator_adaptor :
    iterator_adaptor_detail::super_<
        Derived, Base, Value, Traversal, Reference, Difference
    >::type
{


};


} } // namespace pstade::oven


#endif
