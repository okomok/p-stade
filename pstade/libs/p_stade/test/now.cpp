
#include <boost/range.hpp>


int main()
{
    std::string rng;
    boost::iterator_range<std::string::iterator> iter_rng1(rng);
    boost::iterator_range<std::string::iterator> iter_rng2 = iter_rng1;
}
