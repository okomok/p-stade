#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/use_deduced_form.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/egg/by_perfect.hpp>
#include <pstade/egg/by_cref.hpp>
#include <pstade/egg/by_ref.hpp>
#include <pstade/egg/by_value.hpp>
#include <pstade/egg/function_facade.hpp>


using namespace pstade::egg;


//[code_use_deduced_form_example
struct baby_foo
{
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

/*<< Pass `use_deduced_form` as the last template argument. >>*/
typedef function<baby_foo, boost::use_default, use_deduced_form> op_foo;
//]
typedef function<baby_foo, by_ref, use_deduced_form> op_rfoo;
typedef function<baby_foo, by_cref, use_deduced_form> op_crfoo;

struct baby_vfoo
{
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
typedef function<baby_vfoo, by_value, use_deduced_form> op_vfoo;


struct op_foo_ :
    function_facade<op_foo_, boost::use_default, boost::use_default, use_deduced_form>
{
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
