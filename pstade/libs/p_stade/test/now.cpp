

#include <map>
#include <boost/foreach.hpp>

#include <boost/parameter/aux_/parenthesized_type.hpp>
#define UNPARENTHESIZE BOOST_PARAMETER_PARENTHESIZED_TYPE


int main()
{
    std::map<int, int> m;
    BOOST_FOREACH (
        UNPARENTHESIZE((std::pair<int, int>)) p,
        m )
    {
    }
}

