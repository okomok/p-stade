
#include <cassert>

struct A
{
    A(int) {
        //assert(false);
    }
    
    ~A() {
        assert(false);
    }
};


A foo()
{
    return 3;
}

int main()
{
    foo();
}
