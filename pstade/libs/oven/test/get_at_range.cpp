#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/get_at_range.hpp>


#include <vector>
#include <boost/fusion/tuple/tuple.hpp>
#include <boost/fusion/tuple/make_tuple.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/foreach.hpp>


typedef boost::fusion::tuple<int, char> tup_t;
typedef std::vector<tup_t> rng_t;


namespace fusion_does {

    typedef boost::fusion::tuple<int&> rtup_t;
    BOOST_MPL_ASSERT((boost::is_same< boost::fusion::result_of::value_at_c<rtup_t, 0>::type,
        int&>));

}


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    ::rng_t rng;
    rng.push_back( boost::fusion::make_tuple(3, 'a') );
    rng.push_back( boost::fusion::make_tuple(5, 'b') );

    BOOST_FOREACH (char& ch, rng|got_at< boost::mpl::int_<1> >()) {
        ch = 'c';
    }

    BOOST_FOREACH (char const& ch, rng|got_at_c<1>()) {
        BOOST_CHECK(ch == 'c');
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
