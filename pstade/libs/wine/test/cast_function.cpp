#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/cast_function.hpp>


template<class X>
struct op_my_cast
{
    typedef X result_type;

    X operator()(int i) const
    {
        return i;
    }
};

PSTADE_CAST_FUNCTION1(my_cast, op_my_cast, 1)


template<class X, int Y>
struct op_my_cast_
{
    typedef X result_type;

    X operator()(int i) const
    {
        return i;
    }
};

PSTADE_CAST_FUNCTION1(my_cast_, op_my_cast_, (class)(int))


struct x
{
    x() : m_i(7)
    { }

    explicit x(int i) 
        : m_i(i) 
    { }
    
    x(int i, int j)
        : m_i(i+j)
    { }

    x(int i, int j, int k)
        : m_i(i+j+k)
    { }

    int m_i;
};

template<class X>
struct op_my_make
{
    typedef X result_type;

    template< class A0 >
    X operator()(A0& a0) const
    {
        return X(a0);
    }

    template< class A0, class A1 >
    X operator()(A0& a0, A1& a1) const
    {
        return X(a0, a1);
    }
};

#define PSTADE_CAST_FUNCTION_PARAMS (my_make, (1)(2), op_my_make, 1)
#include <pstade/cast_function.hpp>


template<class X, int N>
struct op_my_make_0_3
{
    typedef X result_type;

    X operator()() const
    {
        return X();
    }

    template< class A0 >
    X operator()(A0& a0) const
    {
        return X(a0);
    }

    template< class A0, class A1, class A2 >
    X operator()(A0& a0, A1& a1, A2& a2) const
    {
        return X(a0, a1, a2);
    }
};

#define PSTADE_CAST_FUNCTION_PARAMS (my_make_0_3, (3)(0)(1), op_my_make_0_3, (class)(int))
#include <pstade/cast_function.hpp>


void test()
{
    {
        BOOST_CHECK( ::my_cast<int>(3) == 3 );
        BOOST_CHECK(( ::my_cast_<int, 1>(3) == 3 ));
    }
    {
        BOOST_CHECK( ::my_make< ::x >(3).m_i == 3 );
        BOOST_CHECK( ::my_make< ::x >(3, 4).m_i == 7 );
    }

    {
        BOOST_CHECK(( ::my_make_0_3< ::x, 0 >().m_i == 7 ));
        BOOST_CHECK(( ::my_make_0_3< ::x, 0 >(3).m_i == 3 ));
        BOOST_CHECK(( ::my_make_0_3< ::x, 0 >(3, 4, 5).m_i == 12 ));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
