#include <boost/test/minimal.hpp>


#include <iostream>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/range.hpp>


template< class Range >
boost::iterator_range<
    boost::reverse_iterator<
        typename boost::range_result_iterator<Range>::type
    >
>
make_reverse_range(Range& rng)
{
    return boost::make_iterator_range(
        boost::make_reverse_iterator(boost::end(rng)),
        boost::make_reverse_iterator(boost::begin(rng))
    );
}

int test_main(int, char*[])
{
    std::vector<int> vect;
    vect.push_back(0), vect.push_back(1), vect.push_back(2);

    BOOST_FOREACH (int x, ::make_reverse_range(vect)) {
        std::cout << x;
    }
    return 0;
}
