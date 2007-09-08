#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/deduced_form.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/egg/by_perfect.hpp>
#include <pstade/egg/by_cref.hpp>
#include <pstade/egg/by_ref.hpp>
#include <pstade/egg/by_value.hpp>
#include <pstade/egg/function_facade.hpp>


using namespace pstade::egg;


//[code_deduced_form_example
struct baby_foo
{
    /*<< This enables the workaround. >>*/
    typedef deduced_form call_strategy;

    template<class Myself, class A1>
    struct apply
    {
        typedef A1 &type;
    };

    /*<< `Result` is given as the first argument using `boost::type`. >>*/
    template<class Result, class A1>
    Result call(boost::type<Result>, A1 &a1) const
    {
        return a1;
    }

    template<class Result, class A1>
    Result call(boost::type<Result>, A1 const &a1) const
    {
        return a1;
    }
};

typedef function<baby_foo> op_foo;
//]
typedef function<baby_foo, by_ref> op_rfoo;
typedef function<baby_foo, by_cref> op_crfoo;

struct baby_vfoo
{
    typedef deduced_form call_strategy;

    template<class Myself, class A1>
    struct apply
    {
        typedef A1 type;
    };

    template<class Result, class A1>
    Result call(boost::type<Result>, A1 &a1) const
    {
        return a1;
    }

    template<class Result, class A1>
    Result call(boost::type<Result>, A1 const &a1) const
    {
        return a1;
    }
};
typedef function<baby_vfoo, by_value> op_vfoo;


struct op_foo_ :
    function_facade<op_foo_>
{
    typedef deduced_form call_strategy;

    template<class Myself, class A1>
    struct apply
    {
        typedef A1 &type;
    };

    template<class Result, class A1>
    Result call(boost::type<Result>, A1 &a1) const
    {
        return a1;
    }

    template<class Result, class A1>
    Result call(boost::type<Result>, A1 const&a1) const
    {
        return a1;
    }
};


void pstade_minimal_test()
{
    int i = 12;
    {
        BOOST_CHECK( &(op_foo()(i)) == &i );
        BOOST_CHECK( op_foo()(12) == 12 );

        BOOST_CHECK( &(op_rfoo()(i)) == &i );

        BOOST_CHECK( &(op_crfoo()(i)) == &i );
        BOOST_CHECK( op_crfoo()(12) == 12 );

        BOOST_CHECK( op_vfoo()(12) == 12 );

        BOOST_CHECK( &(op_foo_()(i)) == &i );
    }
}
