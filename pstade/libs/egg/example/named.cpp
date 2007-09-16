#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: http://www.kmonos.net/alang/boost/classes/parameter.html


#include <pstade/egg/named.hpp>
#include <pstade/egg/keyword.hpp>
#include <pstade/minimal_test.hpp>
#include <iomanip>
#include <iostream>


using namespace pstade::egg;


struct draw_text_impl;

namespace pstade_egg_extension {

    template <>
    struct Parameter<draw_text_impl> :
        use_default_parameter
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
    void operator()(int x, int y, String const& msg, int width) const
    {
        std::cout << "(" << std::setw(width) << x << ","
            << std::setw(width) << y << ") : " << msg << std::endl;
    }
};

keyword<0> const _x = PSTADE_EGG_KEYWORD;
keyword<1> const _y = PSTADE_EGG_KEYWORD;
keyword<2> const _msg = PSTADE_EGG_KEYWORD;
keyword<3> const _width = PSTADE_EGG_KEYWORD;

result_of_named4<draw_text_impl>::type const draw_text = PSTADE_EGG_NAMED_L {} PSTADE_EGG_NAMED_R;


void pstade_minimal_test()
{
    std::string www = "World";

    draw_text(_x=1, _y=2, _msg="Hello");
    draw_text(_msg=www, _x=3, _y=4, _width=8);

    named4(draw_text_impl())(_msg=www, _x=3, _y=4, _width=8);
}
