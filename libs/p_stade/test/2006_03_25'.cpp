#include <boost/test/minimal.hpp>



namespace xxx_detail {

    inline void foo_impl1(int& n)
    {
        ++n;
    }

    inline void foo_impl2(int& n)
    {
        --n;
    }

}

class xxx
{
public:
    void foo()
    {
        xxx_detail::foo_impl1(m1);
        xxx_detail::foo_impl2(m2);
    }

private:
    int m1;
    int m2;
};


void test()
{
    xxx x;
    x.foo();
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
