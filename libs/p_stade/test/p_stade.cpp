
#include <pstade/minimal_test.hpp>
#include <pstade/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>


int const g_i = 999;
struct dummy {};

struct klass
{
#if 0
    template<class From>
    klass(From const &i, typename pstade::enable_if< boost::is_same<From, int> >::type = 0)
    {
        BOOST_CHECK(&i == &g_i);
    }
    klass(int const &i, dummy = dummy())
    {
        BOOST_CHECK(&i == &g_i);
    }
#endif

    klass(int const &i) //__attribute__((noinline))
    {
        BOOST_CHECK(&i == &g_i);
    }

#if 0
    klass(int & i)
    {
        BOOST_CHECK(false);
    }

    virtual ~klass() {}

    klass() {}
#endif
};

int const & from_const(int const &i) { return i; }


void test_fun(klass k)
{
}

klass test_ret()
{
    return g_i;
}

void test()
{
    klass k = from_const(g_i);
}


void pstade_minimal_test()
{
 //   ::test();
//    ::test_fun(g_i);
    ::test_ret();
}
