
#include <memory> // auto_ptr

struct List
{
    template< class X >
    operator std::auto_ptr<X>() const
    {
        return std::auto_ptr<X>(new X());
    }
};

List l;


struct Deque
{
    Deque& operator=(std::auto_ptr<Deque> )
    { return *this; }
};

int main()
{
    Deque d;
    d = l;
//    std::auto_ptr<int> a(l);
}

