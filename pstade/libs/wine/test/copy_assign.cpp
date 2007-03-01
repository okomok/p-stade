#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/copy_assign.hpp>


#include <pstade/automatic.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>


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
    xxx& operator=(X const& x)
    {
        m = x.m;
        return *this;
    }

    int m;
};


void test()
{
    {
        xxx x = auto_cast0(); // of course, works
        BOOST_CHECK( x.m == 10 );
    }
#if 0
    {
        xxx x(3);
        x = auto_cast0(); // never compiles.
        BOOST_CHECK( x.m == 10 );
    }
#endif
    {
        xxx x(3);
        BOOST_CHECK( copy_assign(x, auto_cast0).m == 10 ); // ok.
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
