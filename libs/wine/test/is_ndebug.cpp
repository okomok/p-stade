#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/is_ndebug.hpp>


#include <iostream>
#include <boost/config.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/if.hpp>
#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>


#if defined(NDEBUG)
    BOOST_MPL_ASSERT(( pstade::is_ndebug<> ));
#else
    BOOST_MPL_ASSERT_NOT(( pstade::is_ndebug<> ));
#endif


struct release_impl
{
    static void call()
    {
        BOOST_CHECK(( pstade::is_ndebug<>::value ));
    }
};

struct debug_impl
{
    static void call()
    {
        BOOST_CHECK(( !pstade::is_ndebug<>::value ));
    }
};


void impl(boost::mpl::true_)
{
    BOOST_CHECK(( pstade::is_ndebug<>::value ));
    std::cout << "release mode";
}

void impl(boost::mpl::false_)
{
    BOOST_CHECK(( !pstade::is_ndebug<>::value ));
    std::cout << "debug mode";
}


void test()
{
    using namespace boost::mpl;
    using namespace pstade;
    
    if_< is_ndebug<>,
        release_impl,
        debug_impl
    >::type::call();

    ::impl(is_ndebug<>());
}



int test_main(int, char*[])
{
    ::test();
    return 0;
}
