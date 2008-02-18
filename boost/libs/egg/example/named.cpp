

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: http://www.kmonos.net/alang/boost/classes/parameter.html


#include <boost/egg/named.hpp>
#include <boost/egg/keyword.hpp>
#include "../test/egg_test.hpp"
#include <iomanip>
#include <iostream>


using namespace boost::egg;


struct draw_text_impl;

namespace pstade_egg_extension {

    template <>
    struct named_parameter<draw_text_impl> :
        named_parameter_default
    {
        template<class X, int Index>
        struct default_;

        template<class X>
        struct default_<X, 3>
        {
            typedef int result_type;

            template<class PreArgs>
            result_type operator()(PreArgs const&) const
            {
                return 4;
            }
        };
    };

}

struct draw_text_impl
{
    typedef void result_type;
    
    template<class String>
    void operator()(int x, int y, String const &msg, int width) const
    {
        std::cout << "(" << std::setw(width) << x << ","
            << std::setw(width) << y << ") : " << msg << std::endl;
    }
};

keyword<0> const _x = BOOST_EGG_KEYWORD();
keyword<1> const _y = BOOST_EGG_KEYWORD();
keyword<2> const _msg = BOOST_EGG_KEYWORD();
keyword<3> const _width = BOOST_EGG_KEYWORD();

result_of_named4<draw_text_impl>::type const draw_text = BOOST_EGG_NAMED({});


void egg_test()
{
    std::string www = "World";

    draw_text(_x=1, _y=2, _msg="Hello");
    draw_text(_msg=www, _x=3, _y=4, _width=8);

    named4(draw_text_impl())(_msg=www, _x=3, _y=4, _width=8);
}
