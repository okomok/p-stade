#ifndef PSTADE_OVEN_OPTIONAL_HPP
#define PSTADE_OVEN_OPTIONAL_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/optional/optional_fwd.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/nullptr.hpp>
#include "./extension.hpp"


namespace pstade_oven_extension {


    template< class T_ >
    struct Range< boost::optional<T_> >
    {
        template< class X >
        struct associate;

        template< class T >
        struct associate< boost::optional<T> >
        {
            typedef T *mutable_iterator;
            typedef T const *constant_iterator;
        };

        template< class T >
        struct associate< boost::optional<T&> >
        {
            typedef T *mutable_iterator;
            typedef T *constant_iterator;
        };

        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return x ? boost::addressof(*x) : PSTADE_NULLPTR;
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return x ? boost::addressof(*x) + 1 : PSTADE_NULLPTR;
        }
    };


} // namespace pstade_oven_extension


PSTADE_OVEN_EXTENSION_OF_TEMPLATE((boost)(optional), 1)


#endif
