
#include <cassert>

struct precondition
{
    precondition() { }
    precondition(int ) { }
};

void test3()
{
    precondition();
    {
        assert(true);
        assert(true);
        assert("hello");
    }
}

void test4()
{
    precondition of(3);
    {
        assert(true);
        assert(true);
        assert("hello");
    }
}

struct ctor_precondition
{
    ctor_precondition() { }
    ctor_precondition(int ) { }
};

void test4()
{
    ctor_precondition of(3);
    {
        assert(true);
        assert(true);
        assert("hello");
    }
}

int main()
{
    return 0;
}
