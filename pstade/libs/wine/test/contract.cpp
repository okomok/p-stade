#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/contract.hpp>


#include <iostream>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_integral.hpp>


using namespace pstade;


template< class T >
struct A
{
    void foo()
    {
        PSTADE_CLASS_INVARIANT;
        PSTADE_PRECONDITION(true);

        // do something
        PSTADE_POSTCONDITION(true);
    }

private:

    friend class contract_access;

    bool pstade_invariant() const
    {
        BOOST_MPL_ASSERT((boost::is_integral<T>));

        std::cout << "A holds\n";
        return true;
    }
};


struct B : A<int>
{
    B (int)
    { }
    
    void bar() const
    {
        pstade::class_invariant holds(*this);
        pstade::precondition(true);
        
        // do something

        pstade::postcondition(true);
    }

private:

    friend class contract_access;

    bool pstade_invariant() const
    {
        std::cout << "B holds\n";

        return
            class_invariant::holds< A<int> >(*this) &&
            true
        ;
    }
};


void test()
{
    A<int> a;
    a.foo();
    (void)a;

    BOOST_ASSERT( class_invariant::holds(a) );

    B const b(3);
    b.bar();
    (void)b;

    BOOST_ASSERT( class_invariant::holds(b) );

    for (int i = 0;;) {
        PSTADE_BLOCK_INVARIANT( i < 10 );
        if (++i == 10)
            break;
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
