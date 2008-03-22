

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./egg_test.hpp"


namespace your {

    struct aaa { int v; explicit aaa(int vv):v(vv) {} };
    aaa foo() { return aaa(5); }

    namespace my {

        namespace barrier_of_aaa {
        }

        // my and barrier_of_aaa;
        using namespace barrier_of_aaa; // enclosing my and barrier_of_aaa... is my!

        namespace barrier_of_aaa {
            struct aaa { int v; explicit aaa(int vv):v(vv) {} };
            aaa foo() { return aaa(7); }
        }

        aaa const aaa_obj = foo();
    }

}


void egg_test()
{
    BOOST_CHECK(your::my::aaa_obj.v == 7);
}


namespace A {
    int i;
    namespace B {
        namespace C {
            int i;
        }
        using namespace A::B::C; // enclosing B and C... is B!
        void f1() {
            i = 5; // OK, C::i visible in B and hides A::i
        }
    }
    namespace D {
        using namespace B::C; // enclosing D and C... is A!
        void f2() {
            i = 5; // ambiguous, B::C::i or A::i?
        }
    }
}
