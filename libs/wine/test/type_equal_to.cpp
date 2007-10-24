#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/type_equal_to.hpp>
#include <pstade/minimal_test.hpp>


using namespace pstade;


struct my {};
template<class T> struct your {};


void pstade_minimal_test()
{
    BOOST_CHECK( type_equal_to(typeid(void), typeid(void)) );
    BOOST_CHECK( type_equal_to(typeid(int), typeid(int)) );
    BOOST_CHECK( !type_equal_to(typeid(int), typeid(void)) );

    BOOST_CHECK( type_equal_to(typeid(my), typeid(my)) );
    BOOST_CHECK( type_equal_to(typeid(your<int>), typeid(your<int>)) );
    BOOST_CHECK( !type_equal_to(typeid(my), typeid(your<int>)) );
    BOOST_CHECK( !type_equal_to(typeid(your<double>), typeid(my)) );

    BOOST_CHECK( !type_equal_to(typeid(int), typeid(my)) );
    BOOST_CHECK( !type_equal_to(typeid(your<int>), typeid(my)) );
    BOOST_CHECK( !type_equal_to(typeid(int), typeid(your<int>)) );
    BOOST_CHECK( !type_equal_to(typeid(your<double>), typeid(int)) );
}
