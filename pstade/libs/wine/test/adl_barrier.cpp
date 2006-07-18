#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/adl_barrier.hpp>


// See:
// http://sourceforge.net/mailarchive/message.php?msg_id=14648776
struct using_directive_not_broken
{ };


namespace xxx {

    PSTADE_ADL_BARRIER(aaa) {

        struct aaa { };

    }

    void begin(aaa)
    {
        BOOST_CHECK(false);
    }

    PSTADE_ADL_BARRIER(aaa) {
    }

    struct using_directive_not_broken
    { };

    template< class T >
    struct using_directive_test
    { };

}

namespace yyy {

    PSTADE_ADL_BARRIER(bbb) {

        struct bbb { };

    }

    struct end { };

    struct using_directive_not_broken
    { };

    template< class T >
    struct using_directive_test
    { };

}


namespace zzz {

    struct ccc { };

    PSTADE_ADL_BARRIER_OPEN(ccc)

        void cur(ccc)
        {
            BOOST_CHECK(false);
        }

    PSTADE_ADL_BARRIER_CLOSE(ccc)


    struct using_directive_not_broken
    { };

    template< class T >
    struct using_directive_test
    { };

}


PSTADE_ADL_BARRIER(www) {

    struct www { };

}


void begin(xxx::aaa) { }
void end(yyy::bbb) { }
void cur(zzz::ccc) { }


void test()
{
    xxx::aaa a;
    begin(a);

    yyy::bbb b;
    end(b);

    zzz::ccc c;
    cur(c);

    using_directive_not_broken ok;
    (void)ok;

    ::www w;
    (void)w;
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
