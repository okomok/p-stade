#include <boost/test/minimal.hpp>


namespace aaa {
    namespace bbb {
        struct X { };
        namespace ccc {
            namespace bbb {
                struct Y { };
                namespace ddd {
                    bbb::X x;
                }
            }
        }
    }
}

int test_main(int, char*[])
{
    return 0;
}
