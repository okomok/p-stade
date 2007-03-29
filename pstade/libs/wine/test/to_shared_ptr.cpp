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
#include <pstade/test.hpp>
#include <boost/utility/result_of.hpp>


using namespace pstade;


template<class T>
struct my_ptr
{
    template<class P>
    explicit my_ptr(P p,
        typename enable_if< is_to_shared_ptr_param<T, P> >::type = 0)
        : m_ptr(to_shared_ptr(p))
    { }

    boost::shared_ptr<T> m_ptr;
};


PSTADE_TEST_IS_RESULT_OF((boost::shared_ptr<int>), to_shared_ptr(int *))
PSTADE_TEST_IS_RESULT_OF((boost::shared_ptr<int>), to_shared_ptr(std::auto_ptr<int>))
PSTADE_TEST_IS_RESULT_OF((boost::shared_ptr<int>), to_shared_ptr(boost::shared_ptr<int>))


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
