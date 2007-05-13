
#include <iostream>
#include <cassert>

struct A
{
    A(int) {
        //assert(false);
    }
    
    ~A() {
        std::cout << ",";
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
