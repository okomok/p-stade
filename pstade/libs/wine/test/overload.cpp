#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/overload.hpp>


enum test_code
{
    Point_value,
    const_Point_value,
    Line_value,
    const_Line_value,
    Circle_value,
    const_Circle_value,
    Text_value,
    const_Text_value,
    float_value,
    const_float_value
};


namespace graphics {

    template< class ShapeT >
    test_code draw(ShapeT& x)
    {
        return graphics_draw(x, pstade::overload<>());
    }

    template< class ShapeT >
    test_code draw(const ShapeT& x)
    {
        return graphics_draw(x, pstade::overload<>());
    }

} // namespace graphics


// default
//   Note: const-version isn't required.
//
template< class ShapeT >
test_code graphics_draw(ShapeT& x, pstade::overload<>)
{
    return x.graphics_draw();
}


// intrusive style
//
class Point
{
public:
    test_code graphics_draw()
    {
        return Point_value;
    }

    test_code graphics_draw() const
    {
        return const_Point_value;
    }
};


// non-intrusive style
//
class Line
{ };

inline test_code graphics_draw(Line&, pstade::overload<>)
{
    return Line_value;
}

inline test_code graphics_draw(const Line&, pstade::overload<>)
{
    return const_Line_value;
}


// namespace-intrusive style
//
namespace crop { namespace mystery {

    class Circle
    { };

} } // namespace crop::mistery


namespace crop { namespace mystery { // is not required for pstade::overload<>.

    inline test_code graphics_draw(crop::mystery::Circle&, pstade::overload<>)
    {
        return Circle_value;
    }
    inline test_code graphics_draw(const crop::mystery::Circle&, pstade::overload<>)
    {
        return const_Circle_value;
    }

} }


// partial ordering test
//
namespace never_open {

    template< class CharT >
    class Text
    { };
    
} // namespace never_open


template< class CharT >
test_code graphics_draw(never_open::Text<CharT>&, pstade::overload<>)
{
    return Text_value;
}


template< class CharT >
test_code graphics_draw(const never_open::Text<CharT>&, pstade::overload<>)
{
    return const_Text_value;
}


// built-in type test
//
inline test_code graphics_draw(float&, pstade::overload<>)
{
    return float_value;
}

inline test_code graphics_draw(const float&, pstade::overload<>)
{
    return const_float_value;
}


void test()
{
    {
        Point p;
        BOOST_CHECK( graphics::draw(p) == Point_value );

        Line l;
        BOOST_CHECK( graphics::draw(l) == Line_value );
        
        crop::mystery::Circle c;
        BOOST_CHECK( graphics::draw(c) == Circle_value );
        
        never_open::Text<char> t;
        BOOST_CHECK( graphics::draw(t) == Text_value );

        float f;
        BOOST_CHECK( graphics::draw(f) == float_value );
    }
    {
        const Point p = Point();
        BOOST_CHECK( graphics::draw(p) == const_Point_value );

        const Line l = Line();
        BOOST_CHECK( graphics::draw(l) == const_Line_value );
        
        const crop::mystery::Circle c = crop::mystery::Circle();
        BOOST_CHECK( graphics::draw(c) == const_Circle_value );
        
        const never_open::Text<char> t = never_open::Text<char>();
        BOOST_CHECK( graphics::draw(t) == const_Text_value );

        const float f = 0.0;
        BOOST_CHECK( graphics::draw(f) == const_float_value );
    }

    {
        BOOST_CHECK( graphics::draw(Point()) == const_Point_value );
        BOOST_CHECK( graphics::draw(Line()) == const_Line_value );
        BOOST_CHECK( graphics::draw(crop::mystery::Circle()) == const_Circle_value );
        BOOST_CHECK( graphics::draw(never_open::Text<char>()) == const_Text_value );
        BOOST_CHECK( graphics::draw(float()) == const_float_value );
    }
}


int test_main(int, char*[])
{
    ::test();

    return 0;
}
