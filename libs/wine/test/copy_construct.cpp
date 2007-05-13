#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/copy_construct.hpp>


#include <boost/utility/result_of.hpp>
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


void test_automatic()
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


struct my
{
    /*implicit*/ my(int i)
        : m_i(i)
    { }

    int m_i;
};


void test()
{
    {
        boost::result_of<op_copy_construct<my>(int)>::type
            r = pstade::copy_construct<my>(10);
        BOOST_CHECK(r.m_i == 10);
    }
    {
        boost::result_of<op_copy_construct<char>(int)>::type
            r = pstade::copy_construct<char>(10);
        BOOST_CHECK(r == char(10));
    }
    { // same type (does nothing)
        boost::result_of<op_copy_construct<int>(int)>::type
            r = pstade::copy_construct<int>(10);
        BOOST_CHECK(r == 10);
    }
}


int test_main(int, char*[])
{
    ::test();
    ::test_automatic();
    return 0;
}
