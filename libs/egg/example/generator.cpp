

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/generator.hpp>
#include <utility> // pair
#include <boost/tuple/tuple.hpp>
#include <string>


#include "./egg_example.hpp"


//[code_example_generator
typedef
    generator<
        std::pair< deduce<boost::mpl::_1, as_value>, deduce<boost::mpl::_2, as_value> >
    >::type
T_make_pair;

T_make_pair const make_pair = BOOST_EGG_GENERATOR();

struct tuple_ /*< __BOOST_TUPLE__ template arity is large, so that `mpl::_x` can't be used. >*/
{
    template<class T1, class T2>
    struct apply
    {
        typedef boost::tuples::tuple<T1 &, T2 &> type;
    };
};

generator<tuple_>::type const my_pack = BOOST_EGG_GENERATOR();

void egg_example()
{
    BOOST_CHECK( make_pair(10, std::string("generator"))
        == std::make_pair(10, std::string("generator")) );

    int ten = 10;
    BOOST_CHECK( &(boost::get<1>(my_pack('a', ten))) == &ten );
}
//]
