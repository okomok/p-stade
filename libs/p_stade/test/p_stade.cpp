
#include <boost/range.hpp>
#include <string>

using namespace boost;


int main()
{
    std::string rng; // mutable range

    {// (a)
        std::string::iterator first
            = boost::begin(iterator_range<std::string::iterator>(rng)); // returns mutable iterator
    }
    {// (b)
        std::string::iterator first
            = sub_range<std::string>(rng).begin(); // returns mutable iterator
    }
    {// (c)
        std::string::const_iterator first
            = boost::begin(sub_range<std::string>(rng)); // returns "constant" iterator
    }
}
