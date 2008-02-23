

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/function_facade.hpp>


#include "./egg_example.hpp"


//[code_example_function_facade
template<class T>
struct plus_to :
    function_facade< plus_to<T> >
{
    template<class Me, class A>
    struct apply
    {
        typedef T type;
    };

    template<class Re, class A>
    Re call(A &a) const
    {
        return m_x + a;
    }

    explicit plus_to(T x) : m_x(x)
    {}

private:
    T m_x;
};

/*< `plus_to<>` is already __EGG_MAJOR_FUNCTION_OBJECT__ type. >*/
template<class T>
plus_to<T> make_plus_to(T x)
{
    return plus_to<T>(x);
}

void egg_example()
{
    BOOST_CHECK( make_plus_to(1)(3) == 4 );
}
//]
