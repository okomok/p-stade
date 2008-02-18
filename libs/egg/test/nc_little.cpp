#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function_facade.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/noncopyable.hpp>


namespace egg = pstade::egg;
using namespace egg;


struct little_id : boost::noncopyable
{
    template<class _, class A>
    struct apply { typedef A& type;};

    template<class _, class A>
    _ call(A& a) const { return a; }

    little_id() {};
};

function<little_id> an_id;


struct my_id : boost::noncopyable,
    function_facade<my_id>
{
    template<class _, class A>
    struct apply { typedef A& type;};

    template<class _, class A>
    _ call(A& a) const { return a; }

    my_id() {};
};


void pstade_minimal_test()
{
    {
        int i = 3;
        BOOST_CHECK( an_id(i) == 3 );
        little_id const& l = an_id.little();
        (void)l;
    }
    {
        my_id const id;
        int i = 3;
        BOOST_CHECK( id(i) == 3 );
        my_id::little_type const& l = id.little();
        (void)l;
    }
}
