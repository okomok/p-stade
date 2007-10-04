

#include <boost/lambda/core.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/decay.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/range/begin.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/remove_extent.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/range/begin.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type.hpp>
#include <boost/mpl/not.hpp>
#include <boost/typeof/typeof.hpp>
#include <pstade/unevaluated.hpp>
#include <string>
#include <boost/utility/enable_if.hpp>
#include <pstade/minimal_test.hpp>
#include <pstade/oven/detail/boost_begin_end.hpp>
#include <pstade/junk/vc7_1_range_iterator.hpp>



using ::boost::type_traits::yes_type;
using ::boost::type_traits::no_type;
template<class T> struct wrap {};

template< typename T > T(* is_array_tester1(wrap<T>) )(wrap<T>);
char BOOST_TT_DECL is_array_tester1(...);

template< typename T> no_type is_array_tester2(T(*)(wrap<T>));
yes_type BOOST_TT_DECL is_array_tester2(...);

template< typename T >
struct is_array_impl
{ 
    BOOST_STATIC_CONSTANT(bool, value = 
        sizeof(is_array_tester2(
            is_array_tester1(
                wrap<T>()
                )
        )) == 1
    );
};


struct dummy {};

#if 0
template<class Array>
struct my_range_iterator3
{
    typedef typename boost::remove_extent<Array>::type *type;
    //BOOST_MPL_ASSERT((boost::is_array<Array>));
    //typedef int type;
};

template<class Array>
struct my_range_iterator3<Array const>
{
    typedef typename boost::remove_extent<Array>::type const *type;
    //BOOST_MPL_ASSERT((boost::is_array<Array>));
    //typedef int type;
};
#endif

// deduced context in function declaration.
template<class Array>
struct my_range_iterator3
{
    // Array == T[N] => type == `const T * const` which is bindable `to T *`.
    // Array == T const[N] => type == T * const
    typedef Array type;
};

// metafunction context
template<class T, std::size_t N>
struct my_range_iterator3<T[N]>
{
    typedef T *type;
};


#if 0
template<class T, std::size_t N>
struct my_range_iterator3<T const[N]>
{
    typedef T const *type;
};
#endif


/*
template<class T, std::size_t N>
struct my_range_iterator3<T[N]>
{
    typedef T *type;
};
*/

template<class Array, bool IsArray>
struct my_range_iterator2;

template<class Array>
struct my_range_iterator2<Array, true>
{
    typedef typename my_range_iterator3<Array>::type type;
};

template<class Range>
struct my_range_iterator2<Range, false> : boost::range_iterator<Range>
{};

template<class Range >
struct my_range_iterator :
    boost::vc7_1_range_iterator<Range>
    // Don't use boost::is_array. Partial-spec is broken here in deduced-context of function declaration.
//    my_range_iterator2<Range, is_array_impl<Range>::value>
{};


template<class Range>
typename my_range_iterator<Range>::type
my_begin(Range &rng)
{
    return pstade::oven::boost_begin(rng);
}

template<class Range>
typename my_range_iterator<Range const>::type
my_begin(Range const & rng)
{
    return pstade::oven::boost_begin(rng);
}


template<class X>
void foo(X& )
{
    BOOST_MPL_ASSERT_NOT((boost::is_same<X, int * const>));
};


void pstade_minimal_test()
{
#if 1
    {
        BOOST_MPL_ASSERT((boost::is_same<int *, my_range_iterator< int[2] >::type>));
        int a[] = { 1, 2 };
    //    foo(my_begin(a)); // my_begin(a) returns const int * const
        int * p = my_begin(a);
        BOOST_CHECK(p == &a[0]);
    }

    {
        BOOST_MPL_ASSERT((boost::is_same<int const *, my_range_iterator< int const[2] >::type>));
        int const a[] = { 1, 2 };
        foo(my_begin(a)); // my_begin(a) returns int * const
        int const *p = my_begin(a);
        BOOST_CHECK(p == &a[0]);
    }
#endif
#if 1
    {
        std::string a;
        BOOST_CHECK(a.begin() == my_begin(a));
    }

    {
        std::string const a;
        BOOST_CHECK(a.begin() == my_begin(a));
    }
#endif
}
