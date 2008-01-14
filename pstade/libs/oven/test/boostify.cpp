#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/minimal_test.hpp>
#include <pstade/oven/oven.hpp>


#include <boost/range.hpp>
#include <string>


#if !defined(boost_oven_extension)
    #error extension is not boostified.
#endif

#if !defined(BOOST_OVEN_EXTENSION_OF_TYPE)
    #error extension is not boostified.
#endif

#if !defined(BOOST_OVEN_EXTENSION_OF_TEMPLATE)
    #error extension is not boostified.
#endif


#if !defined(BOOST_OVEN_FOREACH)
    #error foreach is not boostified.
#endif

#if !defined(BOOST_OVEN_FOREACH_TPL)
    #error foreach is not boostified.
#endif


#if !defined(BOOST_OVEN_CHECKED)
    #error checked is not boostified.
#endif


namespace Foo {

    template< class T >
    struct Pair
    {
        T first, last;
    };

} // namespace Foo


namespace boost_oven_extension {

    template< class T >
    struct Range< Foo::Pair<T> >
    {
        template< class X >
        struct associate
        {
            typedef T mutable_iterator;
            typedef T constant_iterator;
        };

        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return x.first;
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return x.last;
        }
    };

} // namespace boost_oven_extension

BOOST_OVEN_EXTENSION_OF_TEMPLATE((Foo)(Pair), (class))


void pstade_minimal_test()
{
    {
        namespace oven = boost::oven;
        std::string str("hello, boost");
        ::Foo::Pair<std::string::iterator> rng = { str.begin(), str.end() };
        BOOST_OVEN_FOREACH (ch, rng|oven::identities) {
            (void)ch;
        }
    }
    {
        using namespace boost::oven;
        BOOST_CHECK( equals(std::string("ABC"), std::string("abc")|upper_chars) );
    }
    {
        BOOST_OVEN_CHECKED(std::string("abc"));
    }
}
