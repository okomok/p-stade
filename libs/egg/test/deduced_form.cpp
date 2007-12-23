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
#include <boost/utility/addressof.hpp>


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

    /*<< `Result` is given with the first argument using `boost::type`. >>*/
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

typedef function<baby_foo> T_foo;
//]
typedef function<baby_foo, by_ref> T_rfoo;
typedef function<baby_foo, by_cref> T_crfoo;

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
typedef function<baby_vfoo, by_value> T_vfoo;


struct T_foo_ :
    function_facade<T_foo_>
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
        BOOST_CHECK( boost::addressof(T_foo()(i)) == &i );
        BOOST_CHECK( T_foo()(12) == 12 );

        BOOST_CHECK( boost::addressof(T_rfoo()(i)) == &i );

        BOOST_CHECK( boost::addressof(T_crfoo()(i)) == &i );
        BOOST_CHECK( T_crfoo()(12) == 12 );

        BOOST_CHECK( T_vfoo()(12) == 12 );

        BOOST_CHECK( boost::addressof(T_foo_()(i)) == &i );
    }
}
