#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.P_Stade;
//
// Copyright Shunsuke Sogame 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm>
#include <map>
#include <boost/assign.hpp>
#include <boost/bind.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/range.hpp>


template<class Range, class Predicate> inline
typename boost::range_iterator<Range>::type
max_element(Range& rng, Predicate pred)
{
    return std::max_element(boost::begin(rng), boost::end(rng), pred);
}

template< class AssocContainer >
struct get_key
{
    typedef typename AssocContainer::key_type const& result_type;

    template< class PairT >
    result_type operator()(PairT& p) const
    {
        return p.first;
    }
};

template< class AssocContainer >
boost::iterator_range<
    boost::transform_iterator<
        ::get_key<AssocContainer>,
        typename boost::range_iterator<AssocContainer>::type
    >
> const
make_map_keys(AssocContainer& ac)
{
    return boost::make_iterator_range(
        boost::make_transform_iterator(boost::begin(ac), ::get_key<AssocContainer>()),
        boost::make_transform_iterator(boost::end(ac), ::get_key<AssocContainer>())
    );
}

void test()
{
    typedef std::map<std::string, double> StringDoubleMap; 
    StringDoubleMap mp = boost::assign::map_list_of("George", 0.0)
                                               ("Bill",   0.0)
                                               ("Ronald", 0.0)
                                               ("Jimmy",  0.0); 

    StringDoubleMap::iterator it = ::max_element(
        ::make_map_keys(mp),
        boost::bind(&std::string::length, _1) < boost::bind(&std::string::length, _2)
    ).base();
    if (it != boost::end(mp)) {
        std::cout << it->first.c_str() << ' ' << it->first.length() << std::endl;
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
