#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/minimal_test.hpp>

#include <pstade/egg/function_facade.hpp>
#include <boost/type_traits/remove_const.hpp>
using namespace pstade::egg;


//[code_plus_to
template<class T>
struct plus_to
    : function_facade< plus_to<T> >
{
    template<class Myself, class A>
    struct apply
    {
        typedef T type;
    };

    template<class Result, class A>
    Result call(A& a) const
    {
        return m_x + a;
    }

    explicit plus_to(T x)
        : m_x(x)
    {}

private:
    T m_x;
};

/*<< `plus_to<>` is already a full-fledged function. >>*/

template<class T>
plus_to<T> make_plus_to(T x)
{
    return plus_to<T>(x);
}

void test()
{
    BOOST_CHECK( make_plus_to(1)(3) == 4 );
}
//]


void pstade_minimal_test()
{
    test();
}
