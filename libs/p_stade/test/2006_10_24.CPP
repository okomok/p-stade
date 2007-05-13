
#include <cassert>


struct B
{
    B() { }

    // implicitly-declared copy-constructor
    // B(B const&); // (1)

    template< class T >
    B(T const& x) // (2)
    {
        assert(false);
    }

};

struct D : B
{
    D() { }

    D(D const& other) : // (3)
        B(static_cast<B const&>(other))
    { }
};


void test1()
{
    D d;
    B b(d); // assertion failed
}


void test2()
{
    D d1;
    D d2(d1); // OK
}

int main()
{
    ::test1();
    //::test2();
}
