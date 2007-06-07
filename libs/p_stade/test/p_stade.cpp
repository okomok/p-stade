
#include <memory>

struct B { virtual ~B() { } };
struct D : B { };

std::auto_ptr<D> new_D()
{
    return std::auto_ptr<D>(new D());
}

namespace x {
 typedef int a;

 namespace y { using x::a; }

}

using namespace x;
using namespace x::y;

a s;

int main()
{
    //std::auto_ptr<D const> pcd = new_D(); // msvc-7.1 crash
    //std::auto_ptr<B> pb = new_D(); // gcc doesn't compile.
}

