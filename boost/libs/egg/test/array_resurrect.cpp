#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/array_resurrect.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


#include <boost/egg/pstade/boost_workaround.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_volatile.hpp>
#include <boost/mpl/assert.hpp>
#include <cstddef>
#include <boost/egg/by_cref.hpp>
#include <boost/mpl/always.hpp>
#include <boost/egg/function_extension.hpp>


template<class A>
struct klass
{
    typedef A& type;
};

template<class T, std::size_t N>
struct klass< T[N] >
{
    BOOST_STATIC_ASSERT(N == 3);
    BOOST_MPL_ASSERT((boost::is_const<T>)); 
    BOOST_MPL_ASSERT((boost::is_array<T[N]>));

    typedef T* type;
};

template<class A>
struct klass2 :
    klass<BOOST_EGG_ARRAY_RESURRECT(A)>
{};

template<class A>
typename klass2<A const>::type foo(A const& a)
{
    return a;
};



template<class A>
struct klass_nonconst
{
    typedef A& type;
};

template<class T, std::size_t N>
struct klass_nonconst< T[N] >
{
    BOOST_STATIC_ASSERT(N == 3);
    BOOST_MPL_ASSERT_NOT((boost::is_const<T>)); 
    BOOST_MPL_ASSERT((boost::is_array<T[N]>));

    typedef T* type;
};

template<class A>
struct klass2_nonconst :
    klass_nonconst<BOOST_EGG_ARRAY_RESURRECT(A)>
{};

template<class A>
typename klass2_nonconst<A>::type foo_nonconst(A& a)
{
    return a;
};



template<class A>
struct klass_volatile
{
    typedef A& type;
};

template<class T, std::size_t N>
struct klass_volatile< T[N] >
{
    BOOST_STATIC_ASSERT(N == 3);
    BOOST_MPL_ASSERT((boost::is_volatile<T>)); 
    BOOST_MPL_ASSERT((boost::is_array<T[N]>));

    typedef T* type;
};

template<class A>
struct klass2_volatile :
    klass_volatile<A> // BOOST_EGG_ARRAY_RESURRECT(A) is uneeded.
{};

template<class A>
typename klass2_volatile<A volatile>::type foo_volatile(A volatile& a)
{
    return a;
};


template<class A>
typename klass2_volatile<A volatile const>::type foo_cv(A volatile const& a)
{
    return a;
};



struct by_my_cref : boost::mpl::always<pstade::egg::by_cref> {};

namespace pstade { namespace egg {

    template<class Lit>
    struct function<Lit, by_my_cref>
    {
        #include BOOST_EGG_FUNCTION_PREAMBLE()

        Lit m_lit;
        Lit little() const { return m_lit; }

        template<class A1, class A2>
        typename apply_little<Lit const, A1 const, A2 const>::type operator()(A1 const& a1, A2 const& a2) const
        {
            return egg::call_little<typename apply_little<Lit const, A1 const, A2 const>::type>(m_lit, a1, a2);
        }
    };

} }

struct my_little
{
    template<class Me, class A1, class A2>
    struct apply;

    template<class Me, class T1, std::size_t N1, class T2, std::size_t N2>
    struct apply<Me, T1[N1], T2[N2]>
    {
        typedef T2 *type;
    };

    template<class Re, class A1, class A2>
    Re call(A1& a1, A2& a2) const
    {
        return a2;
    }
};

typedef pstade::egg::function<my_little, ::by_my_cref> T_my_fun;
T_my_fun const my_fun = {{}};


void pstade_minimal_test()
{
    {
        int a[3];
        int const *x = ::foo(a);
        BOOST_CHECK(x == &a[0]);
    }
    {
        int a[3];
        int *x = ::foo_nonconst(a);
        BOOST_CHECK(x == &a[0]);
    }
    {
        int volatile a[3] = {};
        int volatile *x = ::foo_volatile(a);
        BOOST_CHECK(x == &a[0]);
    }
    {
        int const volatile a[3] = {};
        int const volatile *x = ::foo_cv(a);
        BOOST_CHECK(x == &a[0]);
    }
    {
        int a1[3];
        int a2[6];
        pstade::result_of<T_my_fun(int (&)[3], int(&)[6])>::type x = ::my_fun(a1, a2);
        BOOST_CHECK(x == &a2[0]);
    }
}
