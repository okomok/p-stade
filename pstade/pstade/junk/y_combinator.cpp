

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detect_result_type.hpp>


#include <boost/egg/by_value.hpp>
#include <boost/egg/generator.hpp>
#include <boost/egg/nest.hpp>
#include <boost/egg/lazy.hpp>
#include <boost/egg/curry.hpp>
#include <boost/lambda/if.hpp>
#include <boost/egg/construct.hpp>
#include <boost/function.hpp>
#include <boost/any.hpp>


#include "./using_bll.hpp"
#include "./egg_example.hpp"


struct fib_
{
    typedef int result_type;

    template<class F>
    result_type operator()(F f, int i) const
    {
        return i == 0 ? 1 : i * f(i - 1);
    }
};

result_of_curry2<fib_>::type
    const fib = BOOST_EGG_CURRY2({});


#if 1

template<class A>
struct mu
{
    template<class F>
    explicit mu(F f) : m_unroll(f) { }

    typedef boost::function<A(mu<A>)> unroll_t;
    unroll_t m_unroll;
};

//generator<mu< deduce<boost::mpl::_1, as_value> >, by_value>::type
//    const roll = BOOST_EGG_GENERATOR();

X_construct<boost::any, by_value> roll;


struct little_unroll
{
    template<class Me, class Mu>
    struct apply
    {
        typedef typename Mu::unroll_t type;
    };

    template<class Re, class Mu>
    Re call(Mu m) const
    {
        return m.m_unroll;
    }
};

function<little_unroll, by_value> const unroll = {{}};

#endif

struct T_to_any
{
    template<class T>
    operator T() const { return T(); }
};

T_to_any const to_any = {};


void egg_example()
{
    using bll::_1;
    using bll::_2;

    // See: http://r6.ca/blog/20060919T084800Z.html
    // newtype Mu a = Roll { unroll :: Mu a -> a }
    // unroll :: (Mu a) -> (Mu a -> a)
    // \f -> (\x -> f ((unroll x) x)) (Roll (\x -> f ((unroll x) x)))
#if 1
    int r =
        nest1( nest2(_0_(_1))(nest2(nest2(unroll)(_1_(_1)))(_1_(_1))) )
            ( nest1(roll)( nest2(_0_(_1))(nest2(nest2(unroll)(_1_(_1)))(_1_(_1))) ) )
                      (fib)(5);
#endif
#if 0
    int r =
        nest1( nest2(_0_(_1))(nest2(nest1(unroll)(_1_(_1)))(_1_(_1))(_1_(_2))) )
            ( nest1(roll)( nest2(_0_(_1))(nest2(nest1(unroll)(_1_(_1)))(_1_(_1))(_1_(_2))) ) )
                      (fib)(5);
#endif
#if 0
    int r =
    // \f -> (\g -> f (g g)) (\g -> f (g g))
        nest1(nest2(_0_(_1))(nest2(_1_(_1))(_1_(_1))))(nest2(_0_(_1))(nest2(_1_(_1))(_1_(_1))))
                      (fib)(5);
#endif

    BOOST_CHECK(r == 5*4*3*2*1);
}
