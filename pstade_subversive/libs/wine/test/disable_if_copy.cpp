#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/disable_if_copy.hpp>


#include <boost/mpl/bool.hpp>


using namespace pstade;


template< class T >
struct my_base
{
    typedef my_base type;

// structors
    my_base()
    { }

    template< class A_ >
    my_base(A_&, typename disable_if_copy<type, A_>::type = 0)
    {
        BOOST_CHECK(false);
    }

    template< class A_ >
    my_base(A_ const&)
    {
        BOOST_CHECK(false);
    }

// copy-assignments
    template< class A_ >
    typename disable_if_copy_assign<type, A_>::type
    operator=(A_&)
    {
        BOOST_CHECK(false);
        return *this;
    }

    template< class A_ >
    type&
    operator=(A_ const&)
    {
        BOOST_CHECK(false);
        return *this;
    }
};


template< class T >
struct my_derived :
    ::my_base<T>
{
    my_derived() { }
};


template< class Src, class Dst >
void test_copy()
{
    {// direct
        Src src;
        Dst dst(src);
    }
    {// copy
        Src src;
        Dst dst = src;
    }
    {// copy-assignment
        Src src;
        Dst dst;
        dst = src;
    }
}


void test()
{
    ::test_copy< ::my_base<int>,          ::my_base<int>    >();
    ::test_copy< ::my_base<int>    const, ::my_base<int>    >();
    ::test_copy< ::my_derived<int>,       ::my_derived<int> >();
    ::test_copy< ::my_derived<int> const, ::my_derived<int> >();

#if 0 // rejected
    ::test_copy< ::my_derived<int>,       ::my_base<int>    >();
    ::test_copy< ::my_derived<int> const, ::my_base<int>    >();
#endif
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
