

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/adl_barrier.hpp>
#include "./egg_test.hpp"


// See:
// http://sourceforge.net/mailarchive/message.php?msg_id=14648776
struct using_directive_not_broken
{ };


namespace xxx {

    BOOST_EGG_ADL_BARRIER(aaa) {

        struct aaa { };

    }

    void begin(aaa)
    {
        BOOST_CHECK(false);
    }

    BOOST_EGG_ADL_BARRIER(aaa) {
    }

    struct using_directive_not_broken
    { };

    template< class T >
    struct using_directive_test
    { };

}

namespace yyy {

    BOOST_EGG_ADL_BARRIER(bbb) {

        struct bbb { };

    }

    struct end { };

    struct using_directive_not_broken
    { };

    template< class T >
    struct using_directive_test
    { };

}


BOOST_EGG_ADL_BARRIER(www) {

    struct www { };

}


void begin(xxx::aaa) { }
void end(yyy::bbb) { }


void egg_test()
{
    xxx::aaa a;
    begin(a);

    yyy::bbb b;
    end(b);

    using_directive_not_broken ok;
    (void)ok;

    ::www w;
    (void)w;
}
