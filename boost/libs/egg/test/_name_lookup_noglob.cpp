

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


void foo();
int i = 0;

namespace my {
    void foo();
    int i = 0;
}

namespace your {

    void foo()
    {
        using namespace my;
        foo();
        i;
    }
}

int main() {}
