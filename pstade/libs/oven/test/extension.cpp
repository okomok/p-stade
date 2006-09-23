#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/extension.hpp>


#include <string>
#include <vector>
#include <boost/utility/enable_if.hpp> // enable_if
#include <boost/mpl/or.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/noncopyable.hpp>
#include <pstade/oven/tests.hpp>


namespace mine {

    struct container1 :
        std::vector<int>
    { };

    template< class A, class B >
    struct container2 :
        private boost::noncopyable,
        std::vector<A>
    { };

        template< class T >
        struct is_container2 : boost::mpl::false_ { };

        template< class A, class B >
        struct is_container2< container2<A, B> > : boost::mpl::true_ { };


    namespace inside {

        struct container3 :
            std::vector<char>
        { };

    }

    template< class T >
    struct is_container :
        boost::mpl::or_<
            boost::is_same<T, container1>,
            is_container2<T>,
            boost::is_same<T, inside::container3>
        >
    { };

}


struct your_sequence :
    private boost::noncopyable,
    std::string
{ };



namespace pstade { namespace oven {

    template< class T >
    struct extension<T,
        typename boost::enable_if< mine::is_container<T> >::type >
    {
        template< class X >
        struct meta
        {
            typedef typename X::iterator mutable_iterator;
            typedef typename X::const_iterator constant_iterator;
        };

        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return x.begin();
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return x.end();
        }
    };

    template< >
    struct extension< ::your_sequence >
    {
        template< class X >
        struct meta
        {
            typedef typename X::iterator mutable_iterator;
            typedef typename X::const_iterator constant_iterator;
        };

        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return x.begin();
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return x.end();
        }
    };

} }


PSTADE_OVEN_EXTENSION_TYPE((mine)(container1))
PSTADE_OVEN_EXTENSION_TEMPLATE((mine)(container2), 2)
PSTADE_OVEN_EXTENSION_TYPE((mine)(inside)(container3))

PSTADE_OVEN_EXTENSION_TYPE((your_sequence))


void test()
{
    using namespace pstade;

    mine::container1 cont1;
    mine::container2<int, char> cont2;
    mine::inside::container3 cont3;
    ::your_sequence seq1;

    bool never = false;
    if (never) {
        oven::test_random_access(cont1);
        oven::test_random_access(cont2);
        oven::test_random_access(cont3);
        oven::test_random_access(seq1);
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
