#include <pstade/vodka/drink.hpp>


#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/egg/compose1.hpp>
#include <pstade/egg/uncurry.hpp>
#include <pstade/egg/curry.hpp>
#include <pstade/egg/lambda/bind.hpp>


namespace bll = boost::lambda;
namespace egg = pstade::egg;

int minus(int i, int j)
{
    return i - j;
}



struct f_
{
    typedef int result_type;

    template<class Fun>
    int operator()(Fun fun) const
    {
        int four = 4;
        return fun(four);
    }
};

f_ const f = {};


struct g_
{
    typedef int result_type;

    int operator()(int i, int j) const
    {
        return i - j;
    }
};

g_ const g = {};


struct h1_
{
    typedef int result_type;

    template<class Fun>
    int operator()(int r, Fun fun) const
    {
        int y = 4;
        return r * fun(y);
    }
};

h1_ const h1 = {};


struct h2_
{
    typedef int result_type;

    template<class Fun>
    int operator()(int r, Fun fun) const
    {
        int y = 5;
        return r * fun(y);
    }
};

h2_ const h2 = {};


struct u_
{
    typedef int result_type;

    int operator()(int i, int j, int k) const
    {
        return i + j + k;
    }
};

u_ const u = {};


struct q_
{
    typedef int result_type;

    int operator()(int i) const
    {
        return i+1;
    }
};

q_ const q = {};


void pstade_minimal_test()
{
    int x = 3;
    int y = 4;
    int z = 5;
#if 0
    int i = 10;
// \x -> (\y -> x + y)

    BOOST_CHECK(
        bll::bind(
            bll::_1 + bll::_2,
            bll::_1
        )  (1, 2)
        == 3
    );
    (bll::_1 + bll::protect(bll::_1 + 2))(x);//(y);

    int r = bll::bind(bll::protect(bll::bind(&minus, bll::_1, bll::protect(bll::_1))), bll::_1)(x)(y);

    BOOST_CHECK(r == -1);

// \x -> f(\y -> g(x, y))

    bll::bind(bll::bind(&f,
        bll::bind(&g, bll::_1, bll::protect(bll::_1))
    )
#endif

    // \x -> (\y -> g(x,y))
    BOOST_CHECK(-1 ==
        bll::bind(egg::lambda_bind, g, bll::_1, bll::protect(bll::_1))(x)(y)
    );

    // \x -> f(\y -> g(x,y))
    BOOST_CHECK(-1 ==
        bll::bind(
            f,
            bll::bind(
                bll::unlambda(bll::bind(egg::lambda_bind, g, bll::_1, bll::protect(bll::_1))),
                bll::_1
            )
        )(x)
    );


    // \x -> f(q(x), \y -> g(x,y))

    BOOST_CHECK(-4 ==
        bll::bind(
            h1,
            bll::bind(q, bll::_1),
            bll::bind(
                bll::unlambda(bll::bind(egg::lambda_bind, g, bll::_1, bll::protect(bll::_1))),
                bll::_1
            )
        )(x)
    );

    BOOST_CHECK(-4 ==
        bll::bind(
            h1,
            bll::bind(q, bll::_1),
            bll::bind(
                egg::curry2(g),
                bll::_1
            )
        )(x)
    );

    // \x -> f(\y -> g(x,y))
    BOOST_CHECK(-1 ==
        bll::bind(
            f,
            bll::bind(
                egg::curry2(g),
                bll::_1
            )
        )(x)
    );

    // \x -> h1(r1, \y -> g(x,y))

    int r1 = 5;

    BOOST_CHECK(-5 ==
        bll::bind(h1, r1, bll::bind(egg::curry2(g), bll::_1)) (x)
    );

    BOOST_CHECK(-5 ==
        egg::compose1(egg::curry2(h1)(r1),
            egg::curry2(g)
        ) (x)
    );

    // \x -> h1(r1, \y -> h2(r2, \z -> u(x, y, z)))

    int r2 = 7;

    BOOST_CHECK(r1*(r2*(x+y+z)) ==
        egg::compose1(egg::curry2(h1)(r1),
            egg::curry2(
                egg::compose1(egg::curry2(h2)(r2),
                    egg::uncurry(egg::curry3(u))
                )
            )
        ) (x)
    );
}


#if 0
http://programming.reddit.com/info/2i9d6/comments/c2ib3l

#include <boost/function.hpp>
#include <boost/lambda/bind.hpp>
#include <cmath>
#include <iostream>


template< typename R, typename V1, typename V2 >
boost::function< R ( V2 ) > papply( boost::function< R ( V1, V2 ) > f, V1 v ) {
    return boost::lambda::bind( f, v, boost::lambda::_1 );
}
template< typename R, typename V1, typename V2 >
boost::function< boost::function< R ( V1 ) > ( V2 ) > curry( boost::function< R ( V1, V2 ) > f ) {
    return boost::lambda::bind( papply< R, V1, V2 >, f, boost::lambda::_1 );
}

int main() {
    std::cout << curry( boost::function< float ( float, float ) >( std::powf ) )( 10 )( 3 ) << std::endl;
}
#endif
