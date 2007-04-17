#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/copy_construct.hpp>


#include <pstade/automatic.hpp>


using namespace pstade;


template<class To>
struct op_cast0
{
    typedef To result_type;

    To operator()() const
    {
        return To(10);
    }
};

PSTADE_AUTOMATIC(auto_cast0, (op_cast0<_>))


struct xxx
{
    explicit xxx(int _) : m(_)
    { }

    template< class X >
    explicit xxx(X) // eats anything
        : m(8)
    { }

    int m;
};


void test()
{
    {
        xxx x = auto_cast0; // copy-initialization
        BOOST_CHECK( x.m == 10 );
    }
    {
        BOOST_CHECK( xxx(auto_cast0).m == 8 ); // direct-initialization.
    }
    {
        // force copy-initialization
        BOOST_CHECK( pstade::copy_construct<xxx>(auto_cast0).m == 10 );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
