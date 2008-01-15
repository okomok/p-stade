#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function_extension.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/mpl/always.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_volatile.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <cstddef>
#include <string>
#include <pstade/egg/by_perfect.hpp>
#include <pstade/egg/by_cref.hpp>
#include <pstade/egg/by_ref.hpp>
#include <pstade/egg/const.hpp>
#include <pstade/enable_if.hpp>



struct my_strategy : boost::mpl::always<pstade::egg::by_perfect> {};
struct my_c_strategy : boost::mpl::always<pstade::egg::by_cref> {};


namespace pstade { namespace egg {


    template<class Lit>
    struct function<Lit, my_strategy>
    {
        #include PSTADE_EGG_FUNCTION_PREAMBLE()

        Lit m_lit;
        Lit little() const { return m_lit; }

        template<class A1>
        typename apply_little<Lit const, A1>::type
        operator()(A1& i) const
        {
            return egg::call_little<typename apply_little<Lit const, A1>::type>(m_lit, i);
        }

        template<class A1>
        typename apply_little<Lit const, PSTADE_EGG_DEDUCED_CONST(A1)>::type 
        operator()(A1 const& i) const
        {
            return egg::call_little<typename apply_little<Lit const, PSTADE_EGG_DEDUCED_CONST(A1)>::type>(m_lit, i);
        }
    };

    template<class Lit>
    struct function<Lit, my_c_strategy>
    {
        #include PSTADE_EGG_FUNCTION_PREAMBLE()

        Lit m_lit;
        Lit little() const { return m_lit; }

        template<class A1>
        typename apply_little<Lit const, PSTADE_EGG_DEDUCED_CONST(A1)>::type 
        operator()(A1 const& i) const
        {
            return egg::call_little<typename apply_little<Lit const, PSTADE_EGG_DEDUCED_CONST(A1)>::type>(m_lit, i);
        }
    };

} }


namespace egg = pstade::egg;
using namespace egg;
using pstade::result_of;

struct little_bgn
{
    template<class _, class A>
    struct apply;

    // For *by_perfect* overload resolution, little have to guarantee
    // apply<>::type is well-formed against both const and non-const array.
    // So that, function<L, my_strategy> with EGG_ARRAY_RESURRECT completely works.
    template<class _, class T, std::size_t N>
    struct apply<_, T[N] >
    {
        typedef T *type;
    };

    template<class _, class A>
    _ call(A& a) const
    {
        return a;
    }
};

typedef function<little_bgn, my_strategy> T_my_bgn;
PSTADE_EGG_CONST((T_my_bgn), my_bgn) = {{}};

typedef function<little_bgn, by_perfect> T_per_bgn;
PSTADE_EGG_CONST((T_per_bgn), per_bgn) = {{}};

typedef function<little_bgn, by_ref> T_ref_bgn;
PSTADE_EGG_CONST((T_ref_bgn), ref_bgn) = {{}};

typedef function<little_bgn, by_cref> T_cref_bgn;
PSTADE_EGG_CONST((T_cref_bgn), cref_bgn) = {{}};



struct little_cbgn
{
    template<class _, class A>
    struct apply;

    template<class _, class T, std::size_t N>
    struct apply<_, T [N] >
    {
        BOOST_MPL_ASSERT((boost::is_const<T>));
        typedef T  *type;
    };

    template<class _, class A>
    _ call(A& a) const
    {
        return a;
    }
};

typedef function<little_cbgn, my_c_strategy> T_my_cbgn;
PSTADE_EGG_CONST((T_my_cbgn), my_cbgn) = {{}};


template<class T>
T identity_(T x) { return x; }


void pstade_minimal_test()
{
    {
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_my_bgn(int(&)[3])>::type, int *>));
        int a[3] = {};
        int *p = my_bgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_my_bgn(int(&)[3])>::type, int *>));
    }
    {
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_my_bgn(int const(&)[3])>::type, int const *>));
        int const a[3] = {};
        int const *p = my_bgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_my_bgn(int const(&)[3])>::type, int const *>));
    }


    {
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_per_bgn(int(&)[3])>::type, int *>));
        int a[3] = {};
        int *p = per_bgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_per_bgn(int(&)[3])>::type, int *>));
    }
    {
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_per_bgn(int const(&)[3])>::type, int const *>));
        int const a[3] = {};
        int const *p = per_bgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_per_bgn(int const(&)[3])>::type, int const *>));
    }


    {
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_ref_bgn(int(&)[3])>::type, int *>));
        int a[3] = {};
        int *p = ref_bgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_ref_bgn(int(&)[3])>::type, int *>));
    }
    {
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_ref_bgn(int const(&)[3])>::type, int const *>));
        int const a[3] = {};
        int const *p = ref_bgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_ref_bgn(int const(&)[3])>::type, int const *>));
    }

    {
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_cref_bgn(int(&)[3])>::type, int const *>));
        int a[3] = {};
        int const *p = cref_bgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_cref_bgn(int(&)[3])>::type, int const *>));
    }
    {
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_cref_bgn(int const(&)[3])>::type, int const *>));
        int const a[3] = {};
        int const *p = cref_bgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_cref_bgn(int const(&)[3])>::type, int const *>));
    }
    {
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_cref_bgn(int const(&)[3])>::type, int const *>));
        int a[3] = {};
        int const *p = cref_bgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_cref_bgn(int const(&)[3])>::type, int const *>));
    }

    {
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_my_cbgn(int const(&)[3])>::type, int const *>));
        int const a[3] = {};
        int const *p = my_cbgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_my_cbgn(int const(&)[3])>::type, int const *>));
    }
    {
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_my_cbgn(int const(&)[3])>::type, int const *>));
        int a[3] = {};
        int const *p = my_cbgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_my_cbgn(int const(&)[3])>::type, int const *>));
    }


    {
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_my_cbgn(int const(&)[3])>::type, int const *>));
        int const a[3] = {};
        int const *p = ::identity_(my_cbgn(a));
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_my_cbgn(int const(&)[3])>::type, int const *>));
    }
    {
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_my_cbgn(int const(&)[3])>::type, int const *>));
        int a[3] = {};
        int const *p = ::identity_(my_cbgn(a));
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of<T_my_cbgn(int const(&)[3])>::type, int const *>));
    }
}
