
#include <boost/foreach.hpp>
#include <string>
#include <iostream>


template<class Range>
Range const& identity(Range const& rng)
{
	return rng;
}


int main()
{
    BOOST_FOREACH (char ch, ::identity(std::string("dangling"))) {
        std::cout << ch;
    }
}
