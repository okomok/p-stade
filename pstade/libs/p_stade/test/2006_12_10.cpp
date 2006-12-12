#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <utility>
#include <pstade/object_generator.hpp>
#include <boost/tuple/tuple.hpp>


PSTADE_OBJECT_GENERATOR(my_make_pair, const std::pair, (by_value)(by_value))

PSTADE_OBJECT_GENERATOR_WITH_A_DEFAULT(my_tie, boost::tuples::tuple,
    (by_reference)(by_reference)(by_reference)(by_reference)(by_reference), boost::tuples::null_type)


void test()
{
    BOOST_CHECK( ::my_make_pair(3, 2).first == 3 );

    int x, y, z;
    ::my_tie(x, y, z) = boost::tuples::make_tuple(1, 2, 3);
    BOOST_CHECK( y == 2 );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
