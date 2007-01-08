#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>




struct klass
{

template<class A0>
void foo1(A0&) const
{ }

template<class A0>
void foo1(A0 const&) const
{
    BOOST_CHECK(false);
}


template<class A0, class A1>
void foo2(A0&, A1&) const
{ }

template<class A0, class A1>
void foo2(A0&, A1 const&) const
{
    BOOST_CHECK(false);
}

template<class A0, class A1>
void foo2(A0 const&, A1&) const
{
    BOOST_CHECK(false);
}

template<class A0, class A1>
void foo2(A0 const&, A1 const&) const
{
    BOOST_CHECK(false);
}

}; // struct klass


void test()
{
    int A1[3];
    int A2[3];

    klass().foo1(A1);
    klass().foo2(A1, A2);
}


int test_main(int, char *[])
{
    ::test();
    return 0; 
} 
