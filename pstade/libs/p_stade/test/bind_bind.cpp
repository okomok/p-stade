

#include <pstade/vodka/drink.hpp>
#include <pstade/egg/bll/bind.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/noncopyable.hpp>
#include <pstade/minimal_test.hpp>
#include <pstade/egg/lazy.hpp>


namespace egg = pstade::egg;
namespace bll = boost::lambda;


struct A : private boost::noncopyable
{
    operator int() const { return 30; }
};


struct T_foo
{
    typedef int result_type;

    int operator()(int i, int j, int k) const
    {
        return i + j * k;
    }
};

T_foo const foo = {};


void pstade_minimal_test()
{
    int ignored = 0;

    // unneeded with Boost1.35-.
    int _10 = 10;
    int _20 = 20;
    int _30 = 30;


    BOOST_CHECK( bll::_1 (_10) == 10 );
    BOOST_CHECK( bll::_1 (_10, ignored) == 10 );
    BOOST_CHECK( bll::_1 (_10, ignored, ignored) == 10 );

    BOOST_CHECK( bll::protect(bll::_1)(ignored) (_20) == 20 );
    BOOST_CHECK( bll::protect(bll::_1)(ignored) (_30, ignored, ignored) == 30 );


    egg::T_bll_bind const bind = egg::bll_bind;

    // \x -> (\y -> foo(x, y, 30))
    BOOST_CHECK( 10+20*30 ==
        bind(bind, foo, bll::_1, bll::protect(bll::_1), 30) (_10)(_20)
    );
    /*
        bind(bind, foo, bll::_1, bll::protect(bll::_1), 30) (_10)(_20);
        = bind(_apply(foo, _10), _apply(bll::_1, _10), _apply(bll::protect(bll::_1), _10), _apply(30, _10)) (_20);
        = bind(foo, bll::_1(_10), bll::protect(bll::_1)(_10), 30) (_20);
        = bind(foo, _10, bll::_1, 30) (_20);
        = foo(_apply(_10, _20), _apply(bll::_1, _20), _apply(30, _20));
        = foo(_10, bll::_1(_20), 30);
        = foo(_10, _20, 30);
    */

    // \x -> (\y,z -> foo(x, y, z))
    BOOST_CHECK( 10+20*30 ==
        bind(bind, foo, bll::_1, bll::protect(bll::_1), bll::protect(bll::_2))
            (_10)(_20, _30)
    );

    // \x -> (\y -> (\z -> foo(x, y, z)))
    BOOST_CHECK( 10+20*30 ==
        bind(bind, bind, foo, bll::_1, bll::protect(bll::_1), bll::protect(bll::protect(bll::_1)))
            (_10)(_20)(_30)
    );


    pstade::result_of<egg::T_lazy(egg::T_bll_bind const &)>::type const Bind = egg::lazy(egg::bll_bind);

    BOOST_CHECK( 10+20*30 ==
        Bind(foo, bll::_1, bll::protect(bll::_1), bll::protect(bll::_2))
            (_10)(_20, _30)
    );

    BOOST_CHECK( 10+20*30 ==
        Bind(foo, bll::_1, bll::protect(bll::_1), 30)
            (_10)(_20)
    );

    BOOST_CHECK( 10+20*30 ==
        Bind(bind, foo, bll::_1, bll::protect(bll::_1), bll::protect(bll::protect(bll::_1)))
            (_10)(_20)(_30)
    );




    A _a30;

    BOOST_CHECK( 10+20*30 ==
        bind(foo, bll::_1, bll::_2, boost::ref(_a30))
            (_10, _20)
    );

#if 0 // Boost.Lambda overlooked this; _a30 is copied!
    bind(bind, foo, bll::_1, bll::protect(bll::_1), boost::ref(_a30))
        (_10);
#endif
}
