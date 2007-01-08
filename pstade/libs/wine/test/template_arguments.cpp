#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/template_arguments.hpp>


#include <pstade/test.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp>


using namespace pstade;


template<class T0>
struct klass1
{
    typedef void type;
};

PSTADE_TEST_IS_SAME((template_arguments<int&>), (template_arguments_of< klass1<int&> >::type))
PSTADE_TEST_IS_SAME((klass1<int&>), (template_arguments_copy< template_arguments<int&>, klass1<char> >::type))

typedef
    boost::mpl::apply< template_arguments_of< klass1<boost::mpl::_1> >::type, int >::type
args1_t;

PSTADE_TEST_IS_SAME((klass1<int>), (template_arguments_copy<args1_t, klass1<boost::mpl::_1>  >::type))


template<class T0, class T1 = float>
struct klass2
{
    typedef void type;
};

PSTADE_TEST_IS_SAME((template_arguments<int&, double>), (template_arguments_of< klass2<int&, double> >::type))
PSTADE_TEST_IS_SAME((klass2<int&, double>), (template_arguments_copy< template_arguments<int&, double>, klass2<char, char> >::type))

typedef
    boost::mpl::apply< template_arguments_of< klass2<boost::mpl::_1> >::type, int >::type
args2_t;

PSTADE_TEST_IS_SAME((klass2<int>), (template_arguments_copy< args2_t, klass2<boost::mpl::_1> >::type))



void test()
{
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
