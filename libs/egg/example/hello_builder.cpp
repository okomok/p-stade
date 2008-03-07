

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


//[code_example_hello_builder
#include <boost/egg/function.hpp>
#include <boost/egg/result_of.hpp>
#include <iostream>

using namespace boost::egg;

struct little_identity /*< Conforms __CONCEPT_LITTLE_FUNCTION__. >*/
{
    template<class Me, class T>
    struct apply
    {
        typedef T &type; /*< The return type is depend on argument type. In other words, it is __POLYMORPHIC__. >*/
    };

    template<class Re, class T>
    Re call(T &t) const
    {
        return t;
    }
};

typedef function<little_identity> T_identity; /*< __EGG_FUNCTION__ is one of the __EGG_FUNCTION_BUILDERS__. >*/
T_identity const identity = {{}};

int main()
{
    int i = 10;
    result_of_<T_identity(int &)>::type r = identity(i); /*< `identity` can be used with __BOOST_RESULT_OF__. >*/
    std::cout << r; /*< Prints `10`. >*/

    return 0;
}
//]
