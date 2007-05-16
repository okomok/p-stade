#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_const.hpp>


template<class T>
struct y
{
    BOOST_MPL_ASSERT((boost::is_const<T>));

    typedef int type;
};


typedef y<int> yyy;
typedef y<int>::type a;


template<class T>
struct x : y<T>
{
};


template<class T>
x<T> foo(T&)
{
    return x<T>();
}

template<class T>
x<T const> foo(T const&)
{
    return x<T const>();
}


void test()
{
    ::foo(1);
}


int test_main(int, char *[])
{
    ::test();
    return 0; 
} 
