#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/detail/msvc71_array_resurrect.hpp>


#include <pstade/boost_workaround.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/assert.hpp>


template<class A>
struct klass;


template<class T, std::size_t N>
struct klass< T[N] >
{
    BOOST_STATIC_ASSERT(N == 3);
#if !BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    BOOST_MPL_ASSERT((boost::is_const<T>)); // fails under msvc-7.1, but doesn't affect in instantiation context.
#endif
    typedef T* type;
};


template<class A>
struct klass2 :
#if !BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    klass<A>
#else
    // Hmm, resurrection doesn't work with yet another specialization `klass`,
    // meaning that, all the specialzation has to propagte it using decayed form...
    klass<typename pstade::egg::detail::msvc71_array_resurrect<A>::type>
#endif
{};

template<class A>
typename klass2<A const>::type foo(A const& a)
{
    return 0;
};


int main()
{
    int a[3];
    int const *x = ::foo(a);
}
