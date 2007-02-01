#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/to_shared_ptr.hpp>


#include <boost/shared_ptr.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/new_delete.hpp>


using namespace pstade;


template<class T>
struct my_ptr
{
    template<class P>
    explicit my_ptr(P p,
        typename enable_if< is_shared_ptr_constructible<T, P> >::type = 0)
        : m_ptr(to_shared_ptr(p))
    { }

    boost::shared_ptr<T> m_ptr;
};


void test()
{
    {
        my_ptr<int> p(new int(3));
        BOOST_CHECK( *(p.m_ptr) == 3 );
    }
    {
        my_ptr<int> p(op_new_auto<int>()(3));
        BOOST_CHECK( *(p.m_ptr) == 3 );
    }
    {
        boost::shared_ptr<int> p_(new int(3));
        my_ptr<int> p(p_);
        BOOST_CHECK( *(p.m_ptr) == 3 );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
