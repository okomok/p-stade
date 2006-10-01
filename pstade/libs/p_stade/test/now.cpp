#include <boost/range.hpp>
#include <boost/iterator/counting_iterator.hpp>

int main()
{
    boost::make_iterator_range(
        boost::make_counting_iterator(0),
        boost::make_counting_iterator(5)
    )[2];
}
