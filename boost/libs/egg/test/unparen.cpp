

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/unparen.hpp>
#include "./egg_test.hpp"


#include <map>
#include <utility>
#include <boost/foreach.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>


typedef std::pair<int, double> pair_t;
typedef pair_t const c_pair_t;
typedef pair_t volatile v_pair_t;
typedef pair_t const volatile cv_pair_t;


BOOST_MPL_ASSERT(( boost::is_same< BOOST_EGG_UNPAREN((std::pair<int, double>)), pair_t >));
#if 0 // rejected
    BOOST_MPL_ASSERT(( boost::is_same< BOOST_EGG_UNPAREN((std::pair<int, double>) const), c_pair_t >));
    BOOST_MPL_ASSERT(( boost::is_same< BOOST_EGG_UNPAREN((std::pair<int, double>) volatile), v_pair_t >));
    #if !BOOST_WORKAROUND(__BORLANDC__, < 0x600)
        BOOST_MPL_ASSERT(( boost::is_same< BOOST_EGG_UNPAREN((std::pair<int, double>) const volatile), cv_pair_t >));
    #endif
#endif
BOOST_MPL_ASSERT(( boost::is_same< BOOST_EGG_UNPAREN((void)), void >));


// Workaround:
// I don't know what happens...
#if !defined(BOOST_MSVC)
#define BOOST_EGG_typename typename
#else
#define BOOST_EGG_typename
#endif


template< class T >
void test_dependent()
{
#if !BOOST_WORKAROUND(__BORLANDC__, < 0x600)
    BOOST_FOREACH (
        BOOST_EGG_UNPAREN_TPL((std::pair<int, T>)) p,
        BOOST_EGG_typename BOOST_EGG_UNPAREN((std::map<int, T>))()
    ) {
        (void)p;
        BOOST_CHECK(false);
    }
#endif

    typedef BOOST_EGG_UNPAREN_TPL((std::pair<int, T>)) my_pair;
    typedef typename my_pair::first_type first_t;
}


void egg_test()
{
#if !BOOST_WORKAROUND(__BORLANDC__, < 0x600)
    BOOST_FOREACH (
        BOOST_EGG_UNPAREN((std::pair<int, int>)) p,
        BOOST_EGG_UNPAREN((std::map<int, int>))()
    ) {
        (void)p;
        BOOST_CHECK(false);
    }
#endif

    ::test_dependent<int>();
}
