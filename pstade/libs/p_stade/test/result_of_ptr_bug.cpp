#include <boost/utility/result_of.hpp>

int main()
{
    typedef int (*pf_t)(int);
    typedef boost::result_of<pf_t(int)>::type result1_t; // ok
    typedef boost::result_of<pf_t const(int)>::type result2_t; // doesn't compile.
}
