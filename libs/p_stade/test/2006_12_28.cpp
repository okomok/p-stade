#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <boost/utility/result_of.hpp>


struct op1
{
    template<class FunCall>
    struct result { }; // complete

    template<class Fun>
    struct result<Fun(int)>
    {
        typedef int type;
    };

    int operator()(int x) const
    {
        return x;
    }
};

struct op2
{
    template<class FunCall>
    struct result { }; // complete
 
    template<class Fun>
    struct result<Fun(int&)>
    {
        typedef int type;
    };

    int operator()(int& x) const
    {
        return x;
    }
};


template<class F>
typename boost::result_of<F(int&)>::type
apply(F f, int x)
{
    return f(x);
}

int apply(op1 f, int x)
{
    return f(x);
}


void test()
{
    ::apply(op1(), 1);
    ::apply(op2(), 1);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
