#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/lightweight_copyable.hpp>


#include <string>
#include <boost/mpl/bool.hpp>
#include <boost/range.hpp>
#include <boost/foreach.hpp>


template< class T >
struct a_range :
    boost::iterator_range<T *>
    , private pstade::oven::lightweight_copyable< a_range<T> >
{ };


template< class T >
struct a_range_non_lightweight : a_range<T>
{ };


template< class T >
struct a_range_lightweight : a_range<T>
    , private pstade::oven::lightweight_copyable< a_range_lightweight<T> >
{ };


namespace tempo {

    template< class T >
    struct b_range :
        boost::iterator_range<T *>
        , private pstade::oven::lightweight_copyable< b_range<T> >
    { };

    
    template< class T >
    struct b_range_non_lightweight : b_range<T>
    { };

}

bool is_lightweight_proxy(boost::mpl::true_ *)
{
    return true;
}

bool is_lightweight_proxy(boost::mpl::false_ *)
{
    return false;
}


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        BOOST_CHECK( ::is_lightweight_proxy(
            BOOST_FOREACH_IS_LIGHTWEIGHT_PROXY( ::a_range<int>() )
        ) );

        BOOST_CHECK( !::is_lightweight_proxy(
            BOOST_FOREACH_IS_LIGHTWEIGHT_PROXY( ::a_range_non_lightweight<int>() )
        ) );

        BOOST_CHECK( ::is_lightweight_proxy(
            BOOST_FOREACH_IS_LIGHTWEIGHT_PROXY( ::a_range_lightweight<int>() )
        ) );

        BOOST_CHECK( ::is_lightweight_proxy(
            BOOST_FOREACH_IS_LIGHTWEIGHT_PROXY( tempo::b_range<int>() )
        ) );

        BOOST_CHECK( !::is_lightweight_proxy(
            BOOST_FOREACH_IS_LIGHTWEIGHT_PROXY( tempo::b_range_non_lightweight<int>() )
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
