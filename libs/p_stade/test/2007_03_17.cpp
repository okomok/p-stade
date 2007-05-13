

template<class T>
void foo(T* x) { x->xx; }

struct A {};
struct B : A {};

void foo(A* ) { }

int main() { B b; foo(&b); }
