

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/function_extension.hpp>
#include "./egg_test.hpp"


#include <boost/egg/const.hpp>
#include <boost/egg/return.hpp>


struct my_strategy0;


struct my_strategy1
{
    template<class _, class Arity, class Index>
    struct apply
    {
        typedef boost::egg::by_cref type;
    };
};


namespace boost { namespace egg {

    template<class Lit>
    struct function<Lit, my_strategy0>
    {
        BOOST_EGG_FUNCTION_PREAMBLE()

        Lit m_lit;
        Lit const & little() const { return m_lit; }

    // 0ary
        typename apply_little<Lit const>::type
        operator()() const
        {
            return call_little(m_lit);
        }
    };

    template<class Lit>
    struct function<Lit, my_strategy1>
    {
        BOOST_EGG_FUNCTION_PREAMBLE()

        Lit m_lit;
        Lit const & little() const { return m_lit; }

    // 1ary
        template<class A>
        typename apply_little<Lit const, A const>::type
        operator()(A const &a) const
        {
            return call_little(m_lit, a);
        }
    };

} }


struct little_noop
{
    typedef char nullary_result_type;

    template<class Re>
    Re call() const
    {
        return '0';
    }
};

typedef boost::egg::function<little_noop, my_strategy0> T_noop;
BOOST_EGG_CONST((T_noop), noop) = {{}};


struct little_id
{
    template<class Re, class A>
    struct apply
    {
        typedef A &type;
    };

    template<class Re, class A>
    Re call(A &a) const
    {
        return a;
    }
};

typedef boost::egg::function<little_id, my_strategy1> T_id;
BOOST_EGG_CONST((T_id), id) = {{}};


void egg_test()
{
    BOOST_CHECK( noop() == '0' );
    BOOST_CHECK( id(3) == 3 );
    BOOST_CHECK( boost::egg::return_<int>(id)(3) == 3 );
}
