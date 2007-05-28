#ifndef PSTADE_OVEN_SUB_MATCH_HPP
#define PSTADE_OVEN_SUB_MATCH_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// 'boost::sub_match' is derived from 'std::pair' known as Range, but
// that specializations can't win against "primary" function templates.
// Hence we define...


#include "./detail/prelude.hpp"
#include <boost/regex.hpp>
#include "./extension.hpp"


namespace pstade_oven_extension {


    template< class BidiIter >
    struct Range< boost::sub_match<BidiIter> >
    {
        template< class X >
        struct associate
        {
            typedef typename X::iterator mutable_iterator;
            typedef typename X::const_iterator constant_iterator;
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


PSTADE_OVEN_EXTENSION_OF_TEMPLATE((boost)(sub_match), 1)


#endif
