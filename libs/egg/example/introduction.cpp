

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/pipable.hpp>
#include <boost/egg/function.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <string>
#include <boost/lexical_cast.hpp>


#include "./egg_example.hpp"


//[code_introduction
struct little_plus
{
    template<class Me, class X, class Y>
    struct apply
        : boost::remove_cv<X> /*< Determining return type. >*/
    { };

    template<class Re, class X, class Y>
    Re call(X &x, Y &y) const
    {
        return x + y;
    }
};

typedef function<little_plus> T_plus; /*< Building __CONCEPT_LITTLE_FUNCTION__ into __CONCEPT_MAJOR_FUNCTION_OBJECT__ type. >*/
T_plus const plus = {{}};

void egg_builder()
{
    result_of_<T_plus(int, int)>::type r = plus(1, 2); /*< __BOOST_RESULT_OF__ compatible. >*/
    BOOST_CHECK(r == 3);

    namespace bll = boost::lambda;
    using std::string;
    string one("1");
    BOOST_CHECK("12" == bll::bind(plus, bll::_1, string("2"))(one)); /*< __BOOST_LAMBDA__ compatible. >*/
}

result_of_pipable<T_plus>::type const my_plus = BOOST_EGG_PIPABLE({{}}); /*< __STATIC_INITIALIZATION__ without runtime overhead. >*/

void egg_adaptor()
{
    int r = 1|my_plus(2)|my_plus(3); /*< This is __EXTENSION_METHOD__ emulation in C++. >*/
    BOOST_CHECK(r == 1+2+3);

    result_of_<T_pipable(T_plus const &)>::type your_plus = pipable(plus); /*< Using __EGG_PIPABLE__ as higher-order function. >*/
    BOOST_CHECK((1|your_plus(2)) == 1+2);
}
//]

//[code_introduction_fixed_result
struct T_to_string /*< Egg doesn't appreciate `std::unary_function<>`, because inheriting it keeps types out of __POD__. >*/
{
    typedef std::string result_type; /*< `argument_type` etc is not needed. >*/

    template<class T>
    result_type operator()(T const &t) const
    {
        return boost::lexical_cast<std::string>(t);
    }
};

T_to_string const to_string = {};
//]

void egg_example()
{
    ::egg_builder();
    ::egg_adaptor();

    BOOST_CHECK( to_string(1) == "1" );
}
