#ifndef PSTADE_OVEN_XPRESSIVE_HPP
#define PSTADE_OVEN_XPRESSIVE_HPP
#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./extension.hpp"


namespace boost { namespace xpressive {

    template< class BidiIter >
    struct sub_match;

} }


namespace pstade_oven_extension {


    template< class BidiIter >
    struct Range< boost::xpressive::sub_match<BidiIter> >
    {
        template< class X >
        struct associate
        {
            typedef typename X::iterator mutable_iterator;
            typedef typename X::iterator constant_iterator;
        };

        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return x.first;
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return x.second;
        }
    };


} // namespace pstade_oven_extension


PSTADE_OVEN_EXTENSION_OF_TEMPLATE((boost)(xpressive)(sub_match), 1)


#endif
