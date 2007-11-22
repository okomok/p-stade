#include <pstade/vodka/drink.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/fusion/include/as_vector.hpp>
#include <boost/fusion/include/transform_view.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/begin.hpp>


struct identity
{
    template<class FunCall>
    struct result;

    template<class Fun>
    struct result<Fun(int&)>
    {
        typedef int& type;
    };

    int& operator()(int& i) const
    {
        return i;
    }
};


void test()
{
    typedef boost::fusion::vector<int, int> from_t;
    from_t from(10, 20);
    boost::fusion::transform_view<from_t, ::identity> v(from, ::identity());
    *boost::fusion::begin(v) = 999;
    BOOST_CHECK(boost::fusion::at_c<0>(from) == 999);

    //boost::fusion::as_vector(v);
}


void pstade_minimal_test()
{
    ::test();
}
