#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/is_debug.hpp>


#include <boost/config.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/if.hpp>
#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>


#if !defined(NDEBUG)
    BOOST_MPL_ASSERT(( pstade::is_debug<> ));
#else
    BOOST_MPL_ASSERT_NOT(( pstade::is_debug<> ));
#endif


struct release_impl
{
    static void call()
    {
        BOOST_CHECK(( !pstade::is_debug<>::value ));
    }
};

struct debug_impl
{
    static void call()
    {
        BOOST_CHECK(( pstade::is_debug<>::value ));
    }
};


#if !defined(BOOST_NO_SFINAE)

    template <int> struct dummy { dummy(int) {} };

    template< class T >
    struct enable_if_debug :
        boost::enable_if< pstade::is_debug<>, T >
    { };

    template< class T >
    struct disable_if_debug :
        boost::disable_if< pstade::is_debug<>, T >
    { };

    template< class T >
    typename disable_if_debug<T>::type
    impl(dummy<1> = 0)
    {
        BOOST_CHECK(( !pstade::is_debug<>::value ));
    }

    template< class T >
    typename enable_if_debug<T>::type
    impl(dummy<0> = 0)
    {
        BOOST_CHECK(( pstade::is_debug<>::value ));
    }

#else

    template< class T >
    void impl(T * = 0)
    { }

#endif


void test()
{
    using namespace boost::mpl;
    
    if_< not_< pstade::is_debug<> >,
        release_impl,
        debug_impl
    >::type::call();

    impl<void>();
}


int test_main(int, char*[])
{
    ::test();

    return 0;
}
