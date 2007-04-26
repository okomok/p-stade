

#include <cassert>
#include <boost/range.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <string>

// counting_iterator‚Ìrange‚É‚ÍŽg‚¦‚È‚¢
template<typename LvalueRange>
typename boost::iterator_reference<
    typename boost::range_result_iterator<LvalueRange>::type
>::type
front(LvalueRange &rng)
{
    return *boost::begin(rng);
}

int main()
{
    std::string str("abc");
    assert(&::front(str) == &str[0]);
}
