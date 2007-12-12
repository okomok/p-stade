
#include <list>
#include <string>
#include <boost/tuple/tuple.hpp>
#include <boost/iterator/zip_iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>

int to_value(int const &v)
{
    return v;
}

int main()
{
    std::list<int> rng1;
    std::string rng2;

    boost::make_zip_iterator(
        boost::make_tuple(
            boost::make_transform_iterator(rng1.begin(), &to_value), // BidirectionalInput
            rng2.begin() // RandomAccess
        )
    );
}
