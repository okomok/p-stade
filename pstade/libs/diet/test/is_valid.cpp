#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/diet/is_valid.hpp>


#include <vector>
#include "./diagnostics.hpp"


void test_is_valid()
{
    using namespace pstade;

    mfc::A a;
    mfc::B b;
    mfc::C c;
    diet::is_valid(a);
    diet::is_valid(b);
    diet::is_valid(c);

    V v;
    diet::is_valid(v);

    W w;
    diet::is_valid(w);

    my::Y y;
    diet::is_valid(y);
    
    your::Z z;
    diet::is_valid(z);

    S s;
    T t;
    U u;
    diet::is_valid(s);
    diet::is_valid(t);
    diet::is_valid(u);

    // range test
    std::vector<T> ts;
    diet::is_valid(ts);
}


int test_main(int, char*[])
{
    ::test_is_valid();

    return 0;
}
