#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/alternative.hpp>


#include <pstade/test.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp>


using namespace pstade;


template<class T0>
struct klass1
{
    typedef void type;
};

PSTADE_TEST_IS_SAME((alternative_detail::vector<int&>), (alternative< klass1<int&> >::type))
PSTADE_TEST_IS_SAME((klass1<int&>), (alternative_affect< alternative_detail::vector<int&>, klass1<char> >::type))

typedef
    boost::mpl::apply< alternative< klass1<boost::mpl::_1> >::type, int >::type
alt1_t;

PSTADE_TEST_IS_SAME((klass1<int>), (alternative_affect< alt1_t, klass1<boost::mpl::_1> >::type))


template<class T0, class T1 = float>
struct klass2
{
    typedef void type;
};

PSTADE_TEST_IS_SAME((alternative_detail::vector<int&, double>), (alternative< klass2<int&, double> >::type))
PSTADE_TEST_IS_SAME((klass2<int&, double>), (alternative_affect< alternative_detail::vector<int&, double>, klass2<char, char> >::type))

typedef
    boost::mpl::apply< alternative< klass2<boost::mpl::_1> >::type, int >::type
alt2_t;

PSTADE_TEST_IS_SAME((klass2<int>), (alternative_affect< alt2_t, klass2<boost::mpl::_1> >::type))



void test()
{
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
