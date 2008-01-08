#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/apply_little.hpp>
#include <pstade/egg/call_little.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/egg/function_fwd.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/egg/ambi.hpp>
#include <pstade/egg/const.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/always.hpp>
#include <boost/type_traits/is_same.hpp>


namespace egg = pstade::egg;
using namespace egg;


struct my_strategy
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

BOOST_MPL_ASSERT((detail::is_unary_bytag_of<by_perfect, my_strategy>));
BOOST_MPL_ASSERT((boost::is_same<by_perfect, detail::bytag_at<my_strategy, 1, 0>::type>));
BOOST_MPL_ASSERT((boost::is_same<by_value, detail::bytag_at<my_strategy, 2, 0>::type>));
BOOST_MPL_ASSERT((boost::is_same<by_value, detail::bytag_at<my_strategy, 2, 1>::type>));


namespace pstade { namespace egg {

    template<class Little>
    struct function<Little, my_strategy>
    {
        typedef Little little_type;
        typedef function function_type;

        Little m_little;

        Little little() const
        {
            return m_little;
        }

        template<class Signature>
        struct result : of_apply_little<Signature, Little, my_strategy> {};

        template<class A1>
        typename apply_little<Little, A1>::type operator()(A1& i) const
        {
            return egg::call_little<typename apply_little<Little, A1>::type>(m_little, i);
        }

        template<class A1>
        typename apply_little<Little, A1 const>::type operator()(A1 const& i) const
        {
            return egg::call_little<typename apply_little<Little, A1 const>::type>(m_little, i);
        }

        template<class A1, class A2>
        typename apply_little<Little, A1, A2>::type operator()(A1 i, A2 j) const
        {
            return egg::call_little<typename apply_little<Little, A1, A2>::type>(m_little, i, j);
        }
    };

} }


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
PSTADE_EGG_CONST((T_id1), id1) = {{}};


typedef result_of_pipable<base_mult3, my_strategy>::type T_mult3;
PSTADE_EGG_CONST((T_mult3), mult3) = {{}};
typedef result_of_ambi2<base_plus2, my_strategy>::type T_plus2;
PSTADE_EGG_CONST((T_plus2), plus2) = {{}};


void pstade_minimal_test()
{
    BOOST_CHECK( (3|mult3(4, 5)) == 3*4*5 );

    BOOST_CHECK( plus2(1, 2) == 3 );
    BOOST_CHECK( (1|plus2(2)) == 3 );

    int x = 10;
    BOOST_CHECK( &(id1(x)) == &x );
}
