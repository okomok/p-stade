#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Sausage
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/sausage/enumerate_range.hpp>


#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <boost/mpl/bool.hpp>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/multi_pass_range.hpp>


// normal way
//
template< class T >
struct my_enumerable
{ };

namespace pstade { namespace sausage {


    template< class T >
    struct customization< ::my_enumerable<T> >
    {
        template< class My >
        struct enumerate_argument
        {
            typedef T type;
        };

        template< class Argument, class My, class EnumFtor >
        EnumFtor enumerate(My& , EnumFtor fun)
        {
            return fun; // do nothing
        }
    };


} } // namespace pstade::sausage


// using 'which'
//
struct my_enumerable2
{
};

template< class T >
struct is_my_enumerable2 :
    boost::mpl::false_
{ };

template< >
struct is_my_enumerable2<my_enumerable2> :
    boost::mpl::true_
{ };

namespace pstade { namespace sausage {


    template< class T >
    struct customization<T, typename which< is_my_enumerable2<T> >::type>
    {
        template< class My >
        struct enumerate_argument
        {
            typedef int type;
        };

        template< class Argument, class My, class EnumFtor >
        EnumFtor enumerate(My& , EnumFtor fun)
        {
            return fun; // do nothing
        }
    };


} } // namespace pstade::sausage


// intrusive way
//
struct my_enumerable3
{
    typedef int pstade_sausage_enumerate_argument_type;

    template< class Argument, class EnumFtor >
    EnumFtor pstade_sausage_enumerate(EnumFtor fun)
    {
        return fun; // do nothing
    }
};


template< class FowardRange >
typename boost::range_const_iterator<FowardRange>::type
max_element(const FowardRange& rng)
{
    return std::max_element(boost::begin(rng), boost::end(rng));
}


void test()
{
    using namespace pstade;
    
    {
        std::string src("abcdefghijklmnopqrstuvwxyz");
        BOOST_FOREACH (char ch, src|sausage::enumerated|sausage::enumerated) {
            std::cout << ch;
        }

        BOOST_CHECK(
            oven::equals(
                src |
                    sausage::enumerated|sausage::enumerated|sausage::enumerated|
                    sausage::enumerated|sausage::enumerated|sausage::enumerated|
                    sausage::enumerated|sausage::enumerated|sausage::enumerated,
                src
            )
        );
    }

    {
        std::string src("");
        BOOST_CHECK(
            oven::equals(
                src |
                    sausage::enumerated|sausage::enumerated|sausage::enumerated|
                    sausage::enumerated|sausage::enumerated|sausage::enumerated|
                    sausage::enumerated|sausage::enumerated|sausage::enumerated,
                src
            )
        );
    }

    {
        int src[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        BOOST_CHECK(
            oven::equals(
                src |
                    sausage::enumerated|sausage::enumerated|sausage::enumerated|
                    sausage::enumerated|sausage::enumerated|sausage::enumerated|
                    sausage::enumerated|sausage::enumerated|sausage::enumerated,
                src
            )
        );
    }


    {
        int src[] = { 1, 2, 3, 4, 50, 6, 7, 8, 9, 10 };
        BOOST_CHECK( 50 == 
            *::max_element(
                src |
                    sausage::enumerated|oven::multi_passed
            )
        );
    }

    {
        ::my_enumerable<int> my;
        BOOST_FOREACH(int i, my|sausage::enumerated) {
            (void)i;
            BOOST_CHECK(false);
        }
    }

    {
        ::my_enumerable2 my;
        BOOST_FOREACH(int i, my|sausage::enumerated) {
            (void)i;
            BOOST_CHECK(false);
        }
    }

    {
        ::my_enumerable3 my;
        BOOST_FOREACH(int i, my|sausage::enumerated) {
            (void)i;
            BOOST_CHECK(false);
        }
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
