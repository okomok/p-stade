

#include <cstddef>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_extent.hpp>



// In deduced context of declaration
//   typename xxx<Array const>::type foo(Array const&);
// , `Array const` is broken so that partial specialization can't be applied.
// boost::is_array, is_const and add_const etc never work in this context.

// In the broken array context,
//   1. an array type is broken so that you can't use partial specialization.
//   2. `xxx<Array const>::type` must be well-formed, of course.
//   3. `xxx<Array const>::type` can return a wrong type, which is ignored.

// Of course, there is no way to know whether such a context is broken or not.
//
// The workaround is to distinguish a array type from non-array type using:
//     a legacy is_array which doesn't use partial specialization,
//     or a partial specializaton of decayed form `void(T[])`, which exceptionally works.




template<class X>
struct wrap2;


#if 1
// This must be complete in order to be well-formed.
// This result type is ignored, and "overriden" in the non-broken context.
template<class X>
struct wrap2
{
    typedef void type;
};
#endif


template<>
struct wrap2<int const *>
{
    typedef int const *type;
};


template<class A>
struct wrap
{
    // In the broken context, wrap2< int(*)[2] >::type is instantiated,
    // because remove_extent can do nothing.
    typedef typename wrap2<typename boost::remove_extent<A>::type *>::type type;
};


#if 0 // does't work in broken array context.
template<class T, std::size_t N>
struct wrap<T[N]>
{
    typedef T *type;
};
template<class T, std::size_t N>
struct wrap<T const[N]>
{
    typedef T const *type;
};
#endif


template<class A>
typename wrap<A const>::type
foo(A const&)
{
    return 0;
}

int main()
{
    int a[] = { 1, 2 };
    int const * p = ::foo(a);
    (void)p;
//    ::foo_(a);
}
