

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/template_arguments.hpp>
#include "./egg_test.hpp"


#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/preprocessor/cat.hpp>


using boost::egg::details::template_arguments_of;
using boost::egg::details::template_arguments_copy;


#define Egg_vector(N) boost::mpl::BOOST_PP_CAT(vector, N)


struct klass0
{
    typedef void type; // has no effect.
};

BOOST_MPL_ASSERT((boost::is_same<Egg_vector(0)<>, template_arguments_of< klass0 >::type>));
BOOST_MPL_ASSERT((boost::is_same<klass0, template_arguments_copy< Egg_vector(0)<>, klass0 >::type>))


template<class T0>
struct klass1
{
    typedef void type; // has no effect.
};

BOOST_MPL_ASSERT((boost::is_same<Egg_vector(1)<int&>, template_arguments_of< klass1<int&> >::type>));
BOOST_MPL_ASSERT((boost::is_same<klass1<int&>, template_arguments_copy< Egg_vector(1)<int&>, klass1<char> >::type>));

typedef
    boost::mpl::apply< template_arguments_of< klass1<boost::mpl::_1> >::type, int >::type
args1_t;

BOOST_MPL_ASSERT((boost::is_same<klass1<int>, template_arguments_copy<args1_t, klass1<boost::mpl::_1>  >::type>));


template<class T0, class T1 = float>
struct klass2
{
    typedef void type; // has no effect.
};

BOOST_MPL_ASSERT((boost::is_same<Egg_vector(2)<int&, double>, template_arguments_of< klass2<int&, double> >::type>));
BOOST_MPL_ASSERT((boost::is_same<klass2<int&, double>, (template_arguments_copy< Egg_vector(2)<int&, double>, klass2<char, char> >::type>));

typedef
    boost::mpl::apply< template_arguments_of< klass2<boost::mpl::_1> >::type, int >::type
args2_t;

BOOST_MPL_ASSERT((boost::is_same<klass2<int>, template_arguments_copy< args2_t, klass2<boost::mpl::_1> >::type>));


void egg_test()
{ }
