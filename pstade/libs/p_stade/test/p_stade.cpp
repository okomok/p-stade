#include <pstade/vodka/drink.hpp>


// PStade.p_stade;
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/static_downcast.hpp>
#include <boost/utility/result_of.hpp>

using namespace pstade;

struct base
{
};

struct derived : base
{
    derived() { }
    void foo() const { }
};

int main()
{
    derived const D;
    base const& crB = D;

    boost::result_of<
        op_static_downcast<derived>(base const&)
    >::type d = pstade::static_downcast<derived>(crB);

    pstade::static_downcast<derived>(crB).foo();
}
