#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <pstade/result_of.hpp>
#include <pstade/oven/begin_end.hpp>


namespace my {

    namespace op {

        struct logical_not
        {
            typedef bool result_type;

            template< class A >
            bool operator()(A const& a) const
            {
                return !a;
            }
        };

    }

    op::logical_not const logical_not = { }; // see 8.5.1/8

}


void test()
{
    {
        // 'true/false' is not a lvalue. (2.13.5/1)
        pstade::result_of<my::op::logical_not(bool)>::type a = my::logical_not(true);
        BOOST_CHECK(a == false);
    }
    {
        bool b = false;
        pstade::result_of<my::op::logical_not(bool&)>::type a = my::logical_not(b);
        BOOST_CHECK(a == true);
    }
    {
        using namespace pstade;
        int rng[10]; rng[0] = 10;
        pstade::result_of<oven::op_begin(int(&)[10])>::type first = oven::begin(rng);
        BOOST_CHECK(*first == 10);
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
