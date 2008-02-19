

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy get
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/supply_n.hpp>
#include "./egg_test.hpp"


#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/assert.hpp>


namespace mpl = boost::mpl;
using namespace boost::egg::details;



// non-template can't be PlaceholderExpression.
struct klass0
{
    template<class A = void>
    struct apply
    {
        typedef char type;
    };
};

BOOST_MPL_ASSERT((boost::is_same< supply0<klass0>::type, char >));


template<class X>
struct klass1;

BOOST_MPL_ASSERT((boost::is_same< supply1<klass1<mpl::_1>, int>::type, klass1<int> >));
BOOST_MPL_ASSERT((boost::is_same< supply1<klass1<mpl::_1>, int const>::type, klass1<int const> >));
BOOST_MPL_ASSERT((boost::is_same< supply1<klass1<mpl::_1> const, int>::type, klass1<int> const >));


template<class X, class Y>
struct klass2
{
    typedef int type; // ignored
};

BOOST_MPL_ASSERT((boost::is_same< supply2<klass2<mpl::_1, mpl::_2>, int, char>::type, klass2<int, char> >));
BOOST_MPL_ASSERT((boost::is_same< supply2<klass2<mpl::_1, mpl::_2>, int const, char>::type, klass2<int const, char> >));
BOOST_MPL_ASSERT((boost::is_same< supply2<klass2<mpl::_1, mpl::_2> volatile, int, char const>::type, klass2<int, char const> volatile >));


struct second
{
    template<class A1, class A2, class A3>
    struct apply
    {
        typedef A2 type;
    };
};

BOOST_MPL_ASSERT((boost::is_same< supply3<second, int, double, long>::type, double >));
BOOST_MPL_ASSERT((boost::is_same< supply3<second, int const, char, long>::type, char >));
BOOST_MPL_ASSERT((boost::is_same< supply3<second volatile, int, char const, long>::type, char const >));



void egg_test()
{
}
