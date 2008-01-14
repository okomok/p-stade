#include <pstade/vodka/drink.hpp>

#include <boost/iterator/iterator_traits.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>

#include <vector>


template<typename IT, typename FN>
typename FN::template sig<
    boost::tuples::tuple<FN,
        typename boost::iterator_reference<IT>::type
    >
>::type
my_for_each(IT itBegin, IT itEnd, FN fn)
{
    return fn(*itBegin);
}

int main()
{
    namespace lambda = boost::lambda;
    std::vector<int> vec;
    vec.push_back(2);
    int result = ::my_for_each(vec.begin(), vec.end(), lambda::_1 + 3);
    assert( 5 == result );
}

