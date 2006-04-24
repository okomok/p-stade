#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/adl_barrier.hpp>


namespace xxx {

    PSTADE_ADL_BARRIER_OPEN(aaa)

        struct aaa { };

    PSTADE_ADL_BARRIER_CLOSE(aaa)

    void begin(aaa)
    {
        BOOST_CHECK(false);
    }
}

namespace yyy {

    PSTADE_ADL_BARRIER_OPEN(bbb)

        struct bbb { };

    PSTADE_ADL_BARRIER_CLOSE(bbb)

    struct end { };

}


void begin(xxx::aaa) { }
void end(yyy::bbb) { }


void test()
{
    xxx::aaa a;
    begin(a);

    yyy::bbb b;
    end(b);
}


int test_main(int, char*[])
{
    ::test();

    return 0;
}
