

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/function_extension.hpp>
#include "./egg_test.hpp"


#include <boost/egg/function_fwd.hpp>
#include <boost/egg/pipable.hpp>
#include <boost/egg/const.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/always.hpp>
#include <boost/type_traits/is_same.hpp>


#include "./using_egg.hpp"

//[code_my_strategy_tag
struct my_strategy
{
    template<class _, class Arity, class Index>
    struct apply;

    template<class _>
    struct apply<_, boost::mpl::int_<1>, boost::mpl::int_<0> >
    {
        typedef by_perfect type; /*< You could also use `mpl::vector` and `mpl::at`. >*/
    };

    template<class _, class Index>
    struct apply<_, boost::mpl::int_<2>, Index>
    {
        typedef by_value type;
    };

    template<class _, class Index>
    struct apply<_, boost::mpl::int_<3>, Index>
    {
        typedef by_perfect type;
    };

    template<class _, class Index>
    struct apply<_, boost::mpl::int_<4>, Index>
    {
        typedef by_ref type;
    };
};
//]

BOOST_MPL_ASSERT((boost::is_same<by_perfect, details::bytag_at<my_strategy, 1, 0>::type>));
BOOST_MPL_ASSERT((boost::is_same<by_value, details::bytag_at<my_strategy, 2, 0>::type>));
BOOST_MPL_ASSERT((boost::is_same<by_value, details::bytag_at<my_strategy, 2, 1>::type>));

//[code_my_strategy_function
namespace boost { namespace egg {

    template<class Lit>
    struct function<Lit, my_strategy>
    {
        BOOST_EGG_FUNCTION_PREAMBLE()

        Lit m_lit;
        Lit const & little() const { return m_lit; }

    // 0ary
        typename apply_little<Lit const>::type /*< `apply_little` requires `_Lit` to be const-correct. >*/
        operator()() const
        {
            return call_little(m_lit);
        }

    // 1ary: by_perfect
    //  BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT(1) would be expaneded to these.
        template<class A1>
        typename apply_little<Lit const, A1>::type
        operator()(A1 &a1) const
        {
            return call_little(m_lit, a1);
        }

        template<class A1>
        typename apply_little<Lit const, BOOST_EGG_DEDUCED_CONST(A1)>::type /*< `BOOST_EGG_DEDUCED_CONST` works around msvc-7.1 bug around array. >*/
        operator()(A1 const &a1) const
        {
            return call_little(m_lit, a1);
        }

    // 2ary: by_value
        template<class A1, class A2>
        typename apply_little<Lit const, A1, A2>::type
        operator()(A1 a1, A2 a2) const
        {
            return call_little(m_lit, a1, a2);
        }

    // 3ary: by_perfect
        BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT(3)

    // 4ary: by_ref
        template<class A1, class A2, class A3, class A4>
        typename apply_little<Lit const, A1, A2, A3, A4>::type
        operator()(A1& a1, A2& a2, A3 &a3, A4& a4) const
        {
            return call_little(m_lit, a1, a2, a3, a4);
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
typedef function<little_id1, my_strategy> T_id1;
BOOST_EGG_CONST((T_id1), id1) = {{}};


typedef result_of_pipable<base_mult3, my_strategy>::type T_mult3;
BOOST_EGG_CONST((T_mult3), mult3) = {{}};


struct little_plus3
{
    template<class Me, class A1, class A2, class A3>
    struct apply
    {
        typedef A1 type;
    };

    template<class Re, class A1, class A2, class A3>
    Re call(A 1&a1, A2 &a2, A3 &a3) const
    {
        return a1+a2+a3;
    }
};
typedef function<little_plus3, my_strategy> T_plus3;
BOOST_EGG_CONST((T_plus3), plus3) = {{}};



void egg_test()
{
    BOOST_CHECK( (3|mult3(4, 5)) == 3*4*5 );

    int x = 10;
    BOOST_CHECK( id1() == '0' );
    BOOST_CHECK( &(id1(x)) == &x );
    BOOST_CHECK( plus3(1,2,3) == 1+2+3 );
}
