#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/unparenthesize.hpp>
#include <boost/test/minimal.hpp>


#include <map>
#include <utility>
#include <boost/foreach.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>


typedef std::pair<int, double> pair_t;
typedef pair_t const c_pair_t;
typedef pair_t volatile v_pair_t;
typedef pair_t const volatile cv_pair_t;


BOOST_MPL_ASSERT(( boost::is_same< PSTADE_UNPARENTHESIZE((std::pair<int, double>)), pair_t >));
BOOST_MPL_ASSERT(( boost::is_same< PSTADE_UNPARENTHESIZE((std::pair<int, double>) const), c_pair_t >));
BOOST_MPL_ASSERT(( boost::is_same< PSTADE_UNPARENTHESIZE((std::pair<int, double>) volatile), v_pair_t >));
#if !BOOST_WORKAROUND(__BORLANDC__, < 0x600)
    BOOST_MPL_ASSERT(( boost::is_same< PSTADE_UNPARENTHESIZE((std::pair<int, double>) const volatile), cv_pair_t >));
#endif
BOOST_MPL_ASSERT(( boost::is_same< PSTADE_UNPARENTHESIZE((void)), void >));


// Workaround:
// I don't know what happens...
#if !defined(BOOST_MSVC)
#define PSTADE_WINE_TEST_TYPENAME typename
#else
#define PSTADE_WINE_TEST_TYPENAME
#endif


template< class T >
void test_dependent()
{
#if !BOOST_WORKAROUND(__BORLANDC__, < 0x600)
    BOOST_FOREACH (
        PSTADE_UNPARENTHESIZE_TPL((std::pair<int, T>)) p,
        PSTADE_WINE_TEST_TYPENAME PSTADE_UNPARENTHESIZE((std::map<int, T>))()
    ) {
        (void)p;
        BOOST_CHECK(false);
    }
#endif

    typedef PSTADE_UNPARENTHESIZE_TPL((std::pair<int, T>)) my_pair;
    typedef typename my_pair::first_type first_t;
}


void test()
{
    using namespace pstade;

#if !BOOST_WORKAROUND(__BORLANDC__, < 0x600)
    BOOST_FOREACH (
        PSTADE_UNPARENTHESIZE((std::pair<int, int>)) p,
        PSTADE_UNPARENTHESIZE((std::map<int, int>))()
    ) {
        (void)p;
        BOOST_CHECK(false);
    }
#endif

    ::test_dependent<int>();
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
