#include <boost/test/minimal.hpp>


#include <pstade/if_debug.hpp>
#include <pstade/napkin.hpp>
#include <windows.h>
#include <pstade/napkin/dout.hpp>

using namespace pstade;

PSTADE_IF_DEBUG( napkin::ostream my_os(napkin::dout); )

void test()
{
    PSTADE_IF_DEBUG (
        my_os << "hello, napkin version..." << 0.90 << '\n';
    )
}

int test_main(int, char*[])
{
    ::test();
    return 0;
}
