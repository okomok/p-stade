

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/generator.hpp>
#include "./egg_test.hpp"


#include <boost/utility/addressof.hpp>
#include <boost/egg/is_same_obj.hpp>
#include <boost/ref.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/egg/result_of.hpp>


#include "./using_egg.hpp"


template<class Ref>
struct foo
{
    explicit foo(Ref x) : m_x(x) { }
    Ref m_x;
};


typedef generator< foo< deduce<boost::mpl::_1, as_wrapped_ref> > >::type T_make_foo;
T_make_foo const make_foo = BOOST_EGG_GENERATOR();

BOOST_MPL_ASSERT((boost::is_same<boost::egg::result_of_<T_make_foo(boost::reference_wrapper<int>&)>::type,
                 foo<int&> >));
BOOST_MPL_ASSERT((boost::is_same<boost::egg::result_of_<T_make_foo(boost::reference_wrapper<int> const&)>::type,
                 foo<int&> >));
BOOST_MPL_ASSERT((boost::is_same<boost::egg::result_of_<T_make_foo(boost::reference_wrapper<int>)>::type,
                 foo<int&> >));

BOOST_MPL_ASSERT((boost::is_same<boost::egg::result_of_<T_make_foo(boost::reference_wrapper<int const>&)>::type,
                 foo<int const&> >));
BOOST_MPL_ASSERT((boost::is_same<boost::egg::result_of_<T_make_foo(boost::reference_wrapper<int const> const&)>::type,
                 foo<int const&> >));
BOOST_MPL_ASSERT((boost::is_same<boost::egg::result_of_<T_make_foo(boost::reference_wrapper<int const>)>::type,
                 foo<int const&> >));

BOOST_MPL_ASSERT((boost::is_same<boost::egg::result_of_<T_make_foo(int&)>::type,
                 foo<int> >));
BOOST_MPL_ASSERT((boost::is_same<boost::egg::result_of_<T_make_foo(int const&)>::type,
                 foo<int> >));
BOOST_MPL_ASSERT((boost::is_same<boost::egg::result_of_<T_make_foo(int)>::type,
                 foo<int> >));

void egg_test()
{
    {
        int i = 0;
#if !BOOST_WORKAROUND(BOOST_MSVC, == 1310) // msvc-7.1 copies for some reason.
        BOOST_CHECK( is_same_obj(make_foo(boost::ref(i)).m_x, i) );
#endif
        foo<int&> r = make_foo(boost::ref(i));
        BOOST_CHECK(is_same_obj(r.m_x, i));
        
        foo<int const&> cr = make_foo(boost::cref(i));
        BOOST_CHECK(is_same_obj(r.m_x, i));
    }
    {
        int i = 0;
        BOOST_CHECK( !is_same_obj(make_foo(i).m_x, i) );
    }
}
