#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/to_shared_ptr.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/egg/pstade/enable_if.hpp>
#include <boost/egg/new_auto.hpp>
#include <boost/egg/pstade/test.hpp>


using namespace pstade::egg;
using pstade::enable_if;


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

PSTADE_TEST_IS_RESULT_OF((boost::shared_ptr<int>), T_to_shared_ptr(int *))
PSTADE_TEST_IS_RESULT_OF((boost::shared_ptr<int>), T_to_shared_ptr(std::auto_ptr<int>))
PSTADE_TEST_IS_RESULT_OF((boost::shared_ptr<int>), T_to_shared_ptr(boost::shared_ptr<int>))


struct B { virtual ~B() { } };
struct D : B { };

PSTADE_TEST_IS_RESULT_OF((boost::shared_ptr<B>), X_to_shared_ptr<B>(D *))
PSTADE_TEST_IS_RESULT_OF((boost::shared_ptr<B>), X_to_shared_ptr<B>(std::auto_ptr<D>))
PSTADE_TEST_IS_RESULT_OF((boost::shared_ptr<B>), X_to_shared_ptr<B>(boost::shared_ptr<D>))



void pstade_minimal_test()
{
    {
        my_ptr<int> p(new int(3));
        BOOST_CHECK( *(p.m_ptr) == 3 );
    }
    {
        my_ptr<int> p(X_new_auto<int>()(3));
        BOOST_CHECK( *(p.m_ptr) == 3 );
    }
    {
        boost::shared_ptr<int> p_(new int(3));
        my_ptr<int> p(p_);
        BOOST_CHECK( *(p.m_ptr) == 3 );
    }
}
