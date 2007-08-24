#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/fix.hpp>
#include <pstade/minimal_test.hpp>


#include <iostream>


namespace egg = pstade::egg;
using namespace egg;


struct unfixed_fib
{
    typedef int result_type;

    template<class F>
    int operator()(F f, int x) const
    {
        return x <= 1 ? 1 : (f(x-1) + f(x-2));
    }
};

#if 0
pstade::egg::function<
    pstade::egg::detail::baby_bind1_result<
        pstade::egg::function<
            pstade::egg::fix_detail::baby_uncurried
        >,
        unfixed_fib
    >
>

BOOST_MPL_ASSERT((boost::is_same<pstade::result_of<op_fix(unfixed_fib)>::type, char>));
#endif


struct op_uncurried_fact_
{
    typedef int result_type;

    template<class Fact, class I>
    int operator()(Fact fact, I i) const
    {
        // fact is the fixedpoint.
        return i == 0 ? 1 : i * fact(i-1);
    }
};

typedef result_of_curry2<op_uncurried_fact_>::type op_fact_;
PSTADE_POD_CONSTANT((op_fact_), fact_) = PSTADE_EGG_CURRY2_L {} PSTADE_EGG_CURRY2_R;


struct op_uncurried_wrap
{
    typedef int result_type;

    template<class F, class F_, class P>
    int operator()(F f, F_ f_, P p) const
    {
        // f_ is the fixedpoint
        int r = f(f_)(p); // => fact_(f_)(p) => fact_(fix wrap(fact_))(p)
        std::cout << r << std::endl;
        return r;
    }
};

typedef result_of_curry3<op_uncurried_wrap>::type op_wrap;
PSTADE_POD_CONSTANT((op_wrap), wrap) = PSTADE_EGG_CURRY3_L {} PSTADE_EGG_CURRY3_R;

#if 0
struct op_uncurried_memoize
{
    template<class Myself, class Fun, class Fixed, class Arg>
    struct apply :
        result_of<
            typename result_of<Fun(Fixed&)>::type(Arg&)
        >
    { };

    template<class Result, class Fun, class Fixed, class Arg>
    Result call(Fun& fun, Fixed& fixed, Arg const& arg) const
    {
        typedef std::map<Arg, Result> map_t;
        typedef boost::shared_ptr<map_t> sp_t;

        if (m_pmap.empty()) {
            sp_t sp(new map_t());
            m_pmap = sp;
        }
    
        sp_t sp = boost::any_cast<sp_t>(m_pmap);
        
        typename map_t::iterator it = sp->find(arg);
        if (it != sp->end())
            return it->second;
        else
            return (*sp)[a] = fun(fixed)(arg);
    }

private:
    mutable boost::any m_pmap;
};
#endif


struct op_uncurried_wrap2
{
    typedef int result_type;

    template<class F, class F_, class Ex, class P>
    int operator()(F f, F_ f_, Ex extra, P p) const
    {
        // f_(extra) is the fixedpoint.
        int r = f(f_(extra))(p);
        std::cout << r << std::endl;
        return r;
    }
};

typedef result_of_curry4<op_uncurried_wrap2>::type op_wrap2;
PSTADE_POD_CONSTANT((op_wrap2), wrap2) = PSTADE_EGG_CURRY3_L {} PSTADE_EGG_CURRY3_R;


void pstade_minimal_test()
{
    {
        BOOST_CHECK( 89 == fix( curry2(unfixed_fib()) )(10) );
    }
    {
        BOOST_CHECK( 3628800 == fix(fact_)(10) );
    }
    {
        BOOST_CHECK( 3628800 == fix(wrap(fact_))(10) );
    }
    {
        int initialExtra = 1234;
        BOOST_CHECK( 3628800 == fix(wrap2(fact_))(initialExtra)(10) );
    }
}
