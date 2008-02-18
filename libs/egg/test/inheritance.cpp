

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/function.hpp>
#include "./egg_test.hpp"


#include <boost/egg/result_of.hpp>


#include "./using_egg.hpp"


struct little_identity
{
    template<class Me, class A>
    struct apply
    {
        typedef A& type;
    };

    template<class Re, class A>
    Re call(A & a) const
    {
        return a;
    }
};


struct my_identity : function<little_identity>
{
    boost::egg::result_of<my_identity(int&)>::type bar(int i) const
    {
        return (*this)(i);
    }
};


void egg_test()
{
    my_identity id;
    BOOST_CHECK(id(3) == 3);
}
