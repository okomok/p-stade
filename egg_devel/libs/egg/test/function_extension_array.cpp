

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/function_extension.hpp>
#include "./egg_test.hpp"


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
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/by_cref.hpp>
#include <boost/egg/by_ref.hpp>
#include <boost/egg/const.hpp>



struct my_strategy : boost::mpl::always<boost::egg::by_perfect> {};
struct my_c_strategy : boost::mpl::always<boost::egg::by_cref> {};


namespace boost { namespace egg {


    template<class Lit>
    struct function<Lit, my_strategy>
    {
        BOOST_EGG_FUNCTION_PREAMBLE()

        Lit m_lit;
        Lit const& little() const { return m_lit; }

        template<class A1>
        typename apply_little<Lit const, A1>::type
        operator()(A1& i) const
        {
            return call_little(m_lit, i);
        }

        template<class A1>
        typename apply_little<Lit const, BOOST_EGG_DEDUCED_CONST(A1)>::type 
        operator()(A1 const& i) const
        {
            return call_little(m_lit, i);
        }
    };

    template<class Lit>
    struct function<Lit, my_c_strategy>
    {
        BOOST_EGG_FUNCTION_PREAMBLE()

        Lit m_lit;
        Lit const& little() const { return m_lit; }

        template<class A1>
        typename apply_little<Lit const, BOOST_EGG_DEDUCED_CONST(A1)>::type 
        operator()(A1 const& i) const
        {
            return call_little(m_lit, i);
        }
    };

} }


#include "./using_egg.hpp"
using boost::egg::result_of_;

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
BOOST_EGG_CONST((T_my_bgn), my_bgn) = {{}};

typedef function<little_bgn, by_perfect> T_per_bgn;
BOOST_EGG_CONST((T_per_bgn), per_bgn) = {{}};

typedef function<little_bgn, by_ref> T_ref_bgn;
BOOST_EGG_CONST((T_ref_bgn), ref_bgn) = {{}};

typedef function<little_bgn, by_cref> T_cref_bgn;
BOOST_EGG_CONST((T_cref_bgn), cref_bgn) = {{}};



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
BOOST_EGG_CONST((T_my_cbgn), my_cbgn) = {{}};


template<class T>
T identity_(T x) { return x; }


void egg_test()
{
    {
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_my_bgn(int(&)[3])>::type, int *>));
        int a[3] = {};
        int *p = my_bgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_my_bgn(int(&)[3])>::type, int *>));
    }
    {
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_my_bgn(int const(&)[3])>::type, int const *>));
        int const a[3] = {};
        int const *p = my_bgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_my_bgn(int const(&)[3])>::type, int const *>));
    }


    {
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_per_bgn(int(&)[3])>::type, int *>));
        int a[3] = {};
        int *p = per_bgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_per_bgn(int(&)[3])>::type, int *>));
    }
    {
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_per_bgn(int const(&)[3])>::type, int const *>));
        int const a[3] = {};
        int const *p = per_bgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_per_bgn(int const(&)[3])>::type, int const *>));
    }


    {
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_ref_bgn(int(&)[3])>::type, int *>));
        int a[3] = {};
        int *p = ref_bgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_ref_bgn(int(&)[3])>::type, int *>));
    }
    {
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_ref_bgn(int const(&)[3])>::type, int const *>));
        int const a[3] = {};
        int const *p = ref_bgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_ref_bgn(int const(&)[3])>::type, int const *>));
    }

    {
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_cref_bgn(int(&)[3])>::type, int const *>));
        int a[3] = {};
        int const *p = cref_bgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_cref_bgn(int(&)[3])>::type, int const *>));
    }
    {
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_cref_bgn(int const(&)[3])>::type, int const *>));
        int const a[3] = {};
        int const *p = cref_bgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_cref_bgn(int const(&)[3])>::type, int const *>));
    }
    {
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_cref_bgn(int const(&)[3])>::type, int const *>));
        int a[3] = {};
        int const *p = cref_bgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_cref_bgn(int const(&)[3])>::type, int const *>));
    }

    {
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_my_cbgn(int const(&)[3])>::type, int const *>));
        int const a[3] = {};
        int const *p = my_cbgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_my_cbgn(int const(&)[3])>::type, int const *>));
    }
    {
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_my_cbgn(int const(&)[3])>::type, int const *>));
        int a[3] = {};
        int const *p = my_cbgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_my_cbgn(int const(&)[3])>::type, int const *>));
    }


    {
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_my_cbgn(int const(&)[3])>::type, int const *>));
        int const a[3] = {};
        int const *p = ::identity_(my_cbgn(a));
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_my_cbgn(int const(&)[3])>::type, int const *>));
    }
    {
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_my_cbgn(int const(&)[3])>::type, int const *>));
        int a[3] = {};
        int const *p = ::identity_(my_cbgn(a));
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<result_of_<T_my_cbgn(int const(&)[3])>::type, int const *>));
    }
}
