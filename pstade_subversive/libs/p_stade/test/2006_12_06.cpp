



#include <iostream>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <boost/regex.hpp>


template< class Range >
struct match_range_of :
    boost::iterator_range<
        boost::regex_iterator<
            typename boost::range_result_iterator<Range>::type
        >
    >
{ };


template< class Range, class Regex >
typename match_range_of<Range>::type const
make_match_range(Range& rng, Regex const& re,
                 boost::regex_constants::match_flag_type flag = boost::regex_constants::match_default)
{
    typedef typename match_range_of<Range>::type rng_t;
    typedef typename rng_t::iterator iter_t;
    return rng_t(iter_t(boost::begin(rng), boost::end(rng), re, flag), iter_t());
}


int main()
{
    std::string str("hello world");
    boost::regex re("\\w+");
    BOOST_FOREACH (boost::match_results<std::string::iterator> what, ::make_match_range(str, re)) {
        std::cout << what[0] << std::endl;
    }
}
