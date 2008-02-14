#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/minimal_test.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/egg/poly.hpp>
#include <pstade/result_of.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <string>
#include <boost/lexical_cast.hpp>


using pstade::result_of;
using namespace pstade::egg;


//[code_introduction
template<class X, class Y>
struct mono_plus
{
    // Determining return type
    typedef typename boost::remove_cv<X>::type result_type;

    result_type operator()(X &x, Y &y) const
    {
        return x + y;
    }
};

// Building MajorFunction
typedef poly< mono_plus<boost::mpl::_, boost::mpl::_> >::type T_plus;
T_plus const plus = PSTADE_EGG_POLY();

void test_builder()
{
    // Boost.ResultOf compatible
    result_of<T_plus(int, int)>::type r = plus(1, 2);
    BOOST_CHECK(r == 3);

    // Boost.Lambda compatible
    namespace bll = boost::lambda;
    using std::string;
    string one("1");
    BOOST_CHECK("12" == bll::bind(plus, bll::_1, string("2"))(one));
}

// Static initialization which incurs no runtime overhead.
result_of_pipable<T_plus>::type const my_plus = PSTADE_EGG_PIPABLE({{}});

void test_adaptor()
{
    int r = 1|my_plus(2);
    BOOST_CHECK(r == 3);

    // Dynamic initialization without macros.
    result_of<T_pipable(T_plus const &)>::type your_plus = pipable(plus);
    BOOST_CHECK((1|your_plus(2)) == 3);
}
//]

//[code_introduction_fixed_result
struct T_to_string
{
    typedef std::string result_type;

    template<class T>
    result_type operator()(T const &t) const
    {
        return boost::lexical_cast<std::string>(t);
    }
};

T_to_string const to_string = {};
//]

void pstade_minimal_test()
{
    ::test_builder();
    ::test_adaptor();

    BOOST_CHECK( to_string(1) == "1" );
}
