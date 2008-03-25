

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/function.hpp>
#include <string>
#include <boost/ref.hpp>


#include "./egg_example.hpp"


//[code_example_function
struct little_unwrap
{
    template<class Me, class A>
    struct apply
    {
        typedef A &type; /*< `A` is possibly __CV_QUALIFIED__ but not __REFERENCE_TYPE__. >*/
    };

    template<class Me, class T>
    struct apply< Me, boost::reference_wrapper<T> >
    {
        typedef T &type;
    };

    template<class Me, class T>
    struct apply< Me, boost::reference_wrapper<T> const >
    {
        typedef T &type;
    };

    template<class Re, class A>
    Re call(A &a) const /*< `Re` is `apply<little_unwrap const, A>::type`, which is passed by Egg. >*/
    {
        return a;
    }
};

typedef function<little_unwrap> T_unwrap;
T_unwrap const unwrap = {{}};

void egg_example()
{
    int i = 1;
    BOOST_CHECK( &(unwrap(i)) == &i );
    BOOST_CHECK( &(unwrap(boost::ref(i))) == &i );
}
//]
