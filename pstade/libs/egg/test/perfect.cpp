#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/perfect.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/lambda/core.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>

#include <pstade/result_of_lambda.hpp>
#include <boost/preprocessor/facilities/identity.hpp>


struct my_fun_t
{
    template< class T >
    T operator()(T x, T y) const
    {
        return x + y;
    }
};


struct my_fun0_t
{
    int operator()() const
    {
        return 10;
    }
};


template< class FunctorWithResult >
int foo(FunctorWithResult fun)
{
    typename pstade::result_of<FunctorWithResult(int)>::type x = fun(1, 2);
    return x;
}


int my_fun1(int x)
{
    return x;
}


void pstade_minimal_test()
{
    namespace egg = pstade::egg;
    namespace lambda = boost::lambda;

    ::my_fun_t my_fun;

    {
        BOOST_CHECK( 3 ==
            ::foo( egg::xp_perfect<int>()(my_fun) )
        );
    }

#if 0
    {
        BOOST_CHECK( 3 ==
            3  ::foo( my_fun|forwarded(boost::type<int>()) )
        );
    }
#endif
    { // make lambda perfect!
        BOOST_CHECK( 3 ==
            egg::xp_perfect<>()(
                lambda::bind( egg::xp_perfect<int>()(my_fun), lambda::_1, lambda::_2 )
            )(1, 2)
        );
    }

    ::my_fun0_t my_fun0;
    {
        pstade::result_of<
            pstade::result_of<egg::xp_perfect<int>(my_fun0_t)>::type()
        >::type result = egg::xp_perfect<int>()(my_fun0)();
        BOOST_CHECK( result == 10 );
    }

    {
        BOOST_CHECK( 3 ==
            egg::perfect(&my_fun1)(3)
        );
    }
    {
        BOOST_CHECK( 3 ==
            egg::xp_perfect<>()(&my_fun1)(3)
        );
    }

    {
        // (lambda::_1 + lambda::_2)(1, 2); // error
        BOOST_CHECK( 3 == 
            egg::perfect(lambda::_1 + lambda::_2)(1, 2)
        );
        BOOST_CHECK( 3 == 
            egg::xp_perfect<>()(lambda::_1 + lambda::_2)(1, 2)
        );
    }

    {
        egg::result_of_perfect<my_fun_t, int>::type perf = PSTADE_EGG_PERFECT_RESULT_INITIALIZER(BOOST_PP_IDENTITY({}));
        BOOST_CHECK( perf(1,3) == 4);
    }
}
