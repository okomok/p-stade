

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/function_extension.hpp>


#include <boost/egg/pipable.hpp>
#include <boost/egg/const.hpp>


#include "./egg_example.hpp"


//[code_example_writing_your_strategy_tag
struct your_strategy
{
    template<class _, class Arity, class Index>
    struct apply;

    template<class _>
    struct apply<_, boost::mpl::int_<1>, boost::mpl::int_<0> >
    {
        typedef by_perfect type;
    };

    template<class _, class Index>
    struct apply<_, boost::mpl::int_<2>, Index>
    {
        typedef by_value type;
    };
};
//]

//[code_example_writing_your_strategy_specializing
namespace boost { namespace egg {

    template<class Lit>
    struct function<Lit, your_strategy>
    {
        BOOST_EGG_FUNCTION_PREAMBLE() /*< This must be placed first. >*/

        Lit m_lit;
        Lit const & little() const { return m_lit; }

    // 0ary
        typename apply_little<Lit const>::type /*< `apply_little` requires `_Lit` to be const-correct. >*/
        operator()() const
        {
            return call_little(m_lit);
        }

    // 1ary: by_perfect
        BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT(1, BOOST_PP_IDENTITY(const))  /*< Wrap /cv-qualifier/ with `BOOST_PP_IDENTITY`. Egg supports only `const` for now, though. >*/
    /*  is expanded to...
        template<class A1>
        typename apply_little<Lit const, A1>::type
        operator()(A1 &a1) const
        {
            return call_little(m_lit, a1);
        }

        template<class A1>
        typename apply_little<Lit const, BOOST_EGG_DEDUCED_CONST(A1)>::type
        operator()(A1 const &a1) const
        {
            return call_little(m_lit, a1);
        }
    */

    // 2ary: by_value
        template<class A1, class A2>
        typename apply_little<Lit const, A1, A2>::type
        operator()(A1 a1, A2 a2) const
        {
            return call_little(m_lit, a1, a2);
        }
    };

} }
//]


struct base_mult3
{
    typedef int result_type;

    result_type operator()(int i, int j, int k) const
    {
        return i*j*k;
    }
};

struct base_plus2
{
    typedef int result_type;

    result_type operator()(int i, int j) const
    {
        return i + j;
    }
};

struct little_id1
{
    typedef char nullary_result_type;

    template<class Re>
    Re call() const
    {
        return '0';
    }

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

typedef function<little_id1, your_strategy> T_id1;
BOOST_EGG_CONST((T_id1), id1) = {{}};

typedef result_of_pipable<base_mult3, your_strategy>::type T_mult3;
BOOST_EGG_CONST((T_mult3), mult3) = {{}};


void egg_example()
{
    BOOST_CHECK( (3|mult3(4, 5)) == 3*4*5 );

    int x = 10;
    BOOST_CHECK( id1() == '0' );
    BOOST_CHECK( &(id1(x)) == &x );
}
