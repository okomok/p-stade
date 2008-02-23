

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/get.hpp>
#include <string>
#include <map>
#include <algorithm> // equal
#include <boost/iterator/transform_iterator.hpp>


#include "./egg_example.hpp"


//[code_example_get
void egg_example()
{
    typedef std::map<std::string, int> map_t;
    
    map_t m;
    m["one"] = 1;
    m["two"] = 2;

    int a[] = {1,2};
    boost::transform_iterator<X_get_c<1>, map_t::iterator, int &> it(m.begin(), X_get_c<1>());
    BOOST_CHECK(std::equal(a, a+2, it));
}
//]
