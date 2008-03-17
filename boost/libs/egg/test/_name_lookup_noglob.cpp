

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/bind.hpp>

#include <boost/lambda/core.hpp>
#include <boost/mpl/placeholders.hpp>


void foo();
int i = 0;


namespace my {
    void foo();
    int i = 0;
}

namespace your {

#if 1
    void bar()
    {
        using namespace my;
        foo(); // ambiguous
        i; // ambiguous
    }

    void buz()
    {
        using namespace boost::lambda;
        _1; // ambiguous
    }

    void bug()
    {
        using namespace boost::mpl::placeholders;
        _1; // ambiguous
    }
#endif

    void hog()
    {
        using boost::lambda::_1;
        _1; // ok
    }

    void hug()
    {
        namespace bll = boost::lambda;
        bll::_1; // ok
    }
}

int main() {}
