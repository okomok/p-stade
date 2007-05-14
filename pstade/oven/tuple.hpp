#ifndef PSTADE_OVEN_TUPLE_HPP
#define PSTADE_OVEN_TUPLE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/tuple/tuple.hpp>
#include "./extension.hpp"


namespace pstade_oven_extension {


    template< class Iter >
    struct Range< boost::tuples::tuple<Iter, Iter> >
    {
        template< class X >
        struct associate
        {
            typedef Iter mutable_iterator;
            typedef Iter constant_iterator;
        };

        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return boost::tuples::get<0>(x);
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return boost::tuples::get<1>(x);
        }
    };


    template< class Iter >
    struct Range< boost::tuples::cons<Iter, boost::tuples::cons<Iter, boost::tuples::null_type> > >
    {
        template< class X >
        struct associate
        {
            typedef Iter mutable_iterator;
            typedef Iter constant_iterator;
        };

        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return boost::tuples::get<0>(x);
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return boost::tuples::get<1>(x);
        }
    };


} // namespace pstade_oven_extension


PSTADE_OVEN_EXTENSION_OF_TEMPLATE((boost)(tuples)(tuple), 2)


#endif
