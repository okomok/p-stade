
struct A
{
    A() { }
 template<class X> A(X x) { x.f(); }
};

struct B
{
    operator A() const { return A(); }
};

int main() { A a = B(); }
