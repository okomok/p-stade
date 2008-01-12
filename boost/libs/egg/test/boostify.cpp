#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/function.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/pipable.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


struct little_id1
{
    template<class Me, class A>
    struct apply
    {
        typedef A & type;
    };

    template<class Re, class A>
    Re call(A& a) const
    {
        return a;
    }
};

typedef boost::egg::function<little_id1> T_id1;
BOOST_EGG_CONST((T_id1), id1) = {{}};

typedef boost::egg::result_of_pipable<T_id1>::type T_id1_pi;
BOOST_EGG_CONST((T_id1_pi), id1_pi) = BOOST_EGG_PIPABLE({{}});

void pstade_minimal_test()
{
    {
        int x = 10;
        BOOST_CHECK( &(id1(x)) == &x );
        BOOST_CHECK( &(x|id1_pi) == &x );
    }
}
