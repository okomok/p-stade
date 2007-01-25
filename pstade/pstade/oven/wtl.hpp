#ifndef PSTADE_OVEN_WTL_HPP
#define PSTADE_OVEN_WTL_HPP



// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)



// forward declarations
//


#include <pstade/apple/wtl/ctrlw_fwd.hpp> // CSimpleStack

namespace WTL {
    class CString;
}



// range extensions
//


#include <boost/foreach.hpp>
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/const_overloaded.hpp>
#include "./atl.hpp"
#include "./extension.hpp"


namespace pstade_oven_extension {


    template< >
    struct Range< WTL::CString >
    {
        template< class X >
        struct associate
        {
            typedef TCHAR *mutable_iterator;
            typedef TCHAR const *constant_iterator;
        };

        template< class Iterator, class X >
        Iterator begin(X& x PSTADE_CONST_OVERLOADED(X))
        {
            return x.GetBuffer(0);
        }

        template< class Iterator, class X >
        Iterator begin(X const& x)
        {
            return x;
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return begin<Iterator>(x) + x.GetLength();
        }

        template< class X, class From >
        X copy(From& rng)
        {
            X x;
            BOOST_FOREACH (TCHAR ch, rng) {
                x += ch;
            }

            return x;
        }
    };


    template< class T >
    struct Range< WTL::CSimpleStack<T> > :
        Range< ATL::CSimpleArray<T> >
    { };


} // namespace pstade_oven_extension


PSTADE_OVEN_EXTENSION_OF_TYPE((WTL)(CString))
PSTADE_OVEN_EXTENSION_OF_TEMPLATE((WTL)(CSimpleStack), 1)


#endif
