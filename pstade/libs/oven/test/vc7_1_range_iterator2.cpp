#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/detail/vc7_1_range_iterator.hpp>


#include <pstade/minimal_test.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <utility> // pair
#include <string>
#include <pstade/oven/detail/boost_begin_end.hpp>


using pstade::oven::boost_begin;
using pstade::oven::boost_end;
using boost::vc7_1_range_iterator;


// incomplete check.
struct udt;
struct udt_range;

namespace boost {
    template<>
    struct range_mutable_iterator<udt_range>
    {
        typedef char *type;
    };
    template<>
    struct range_const_iterator<udt_range>
    {
        typedef char const *type;
    };
};


template<class Range>
typename vc7_1_range_iterator<Range>::type
my_begin(Range& rng)
{
    return boost_begin(rng);
}

template<class Range>
typename vc7_1_range_iterator<typename boost::add_const<Range>::type>::type
my_begin(Range const& rng)
{
    return boost_begin(rng);
}


BOOST_MPL_ASSERT((boost::is_same<int *, vc7_1_range_iterator<int [8]>::type>));
BOOST_MPL_ASSERT((boost::is_same<int const *, vc7_1_range_iterator<int const[8]>::type>));

BOOST_MPL_ASSERT((boost::is_same<udt *, vc7_1_range_iterator<udt [8]>::type>));
BOOST_MPL_ASSERT((boost::is_same<udt const *, vc7_1_range_iterator<udt const[8]>::type>));

BOOST_MPL_ASSERT((boost::is_same<int *, vc7_1_range_iterator< std::pair<int *, int * > >::type>));
BOOST_MPL_ASSERT((boost::is_same<int const *, vc7_1_range_iterator< std::pair<int const *, int const * > >::type>));
BOOST_MPL_ASSERT((boost::is_same<int *, vc7_1_range_iterator< std::pair<int *, int * > const >::type>));
BOOST_MPL_ASSERT((boost::is_same<int const *, vc7_1_range_iterator< std::pair<int const *, int const * > const >::type>));

BOOST_MPL_ASSERT((boost::is_same<std::string::iterator, vc7_1_range_iterator<std::string>::type>));
BOOST_MPL_ASSERT((boost::is_same<std::string::const_iterator, vc7_1_range_iterator<std::string const>::type>));
BOOST_MPL_ASSERT((boost::is_same<char *, vc7_1_range_iterator<udt_range>::type>));
BOOST_MPL_ASSERT((boost::is_same<char const *, vc7_1_range_iterator<udt_range const>::type>));


struct udt { udt(int) {} };


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        BOOST_MPL_ASSERT((boost::is_same<int *, vc7_1_range_iterator<int [8]>::type>));
        int rng[8] = { 0,1,2,3,4,5,6,7 };
        BOOST_CHECK( my_begin(rng) == &rng[0] );
        BOOST_MPL_ASSERT((boost::is_same<int *, vc7_1_range_iterator<int [8]>::type>));

        vc7_1_range_iterator<int[8]>::type f = my_begin(rng);
        BOOST_CHECK( f == &rng[0] );
        *f = 8;
        BOOST_CHECK( rng[0] == 8 );

        int *f_ = my_begin(rng);
        BOOST_CHECK( f_ == &rng[0] );
        *f_ = 9;
        BOOST_CHECK( rng[0] == 9 );
    }
    {
        BOOST_MPL_ASSERT((boost::is_same<int const *, vc7_1_range_iterator<int const [8]>::type>));
        int const rng[8] = { 0,1,2,3,4,5,6,7 };
        BOOST_CHECK( my_begin(rng) == &rng[0] );
        BOOST_MPL_ASSERT((boost::is_same<int const *, vc7_1_range_iterator<int const [8]>::type>));

        vc7_1_range_iterator<int const[8]>::type f = my_begin(rng);
        BOOST_CHECK( f == &rng[0] );

        int const *f_ = my_begin(rng);
        BOOST_CHECK( f_ == &rng[0] );
    }
    {
        BOOST_MPL_ASSERT((boost::is_same<udt *, vc7_1_range_iterator<udt [8]>::type>));
        udt rng[8] = { 0,1,2,3,4,5,6,7 };
        BOOST_CHECK( my_begin(rng) == &rng[0] );
        BOOST_MPL_ASSERT((boost::is_same<udt *, vc7_1_range_iterator<udt [8]>::type>));

        vc7_1_range_iterator<udt[8]>::type f = my_begin(rng);
        BOOST_CHECK( f == &rng[0] );

        udt *f_ = my_begin(rng);
        BOOST_CHECK( f_ == &rng[0] );
    }
    {
        BOOST_MPL_ASSERT((boost::is_same<udt const *, vc7_1_range_iterator<udt const[8]>::type>));
        udt const rng[8] = { 0,1,2,3,4,5,6,7 };
        BOOST_CHECK( my_begin(rng) == &rng[0] );
        BOOST_MPL_ASSERT((boost::is_same<udt const *, vc7_1_range_iterator<udt const[8]>::type>));

        vc7_1_range_iterator<udt const[8]>::type f = my_begin(rng);
        BOOST_CHECK( f == &rng[0] );

        udt const *f_ = my_begin(rng);
        BOOST_CHECK( f_ == &rng[0] );
    }
    {
        BOOST_MPL_ASSERT((boost::is_same<std::string::iterator, vc7_1_range_iterator<std::string>::type>));
        std::string rng("01234567");
        BOOST_CHECK( my_begin(rng) == rng.begin() );
        BOOST_MPL_ASSERT((boost::is_same<std::string::iterator, vc7_1_range_iterator<std::string>::type>));

        vc7_1_range_iterator<std::string>::type f = my_begin(rng);
        BOOST_CHECK( f == rng.begin() );
        *f = '8';
        BOOST_CHECK( rng[0] == '8' );
    }
    {
        BOOST_MPL_ASSERT((boost::is_same<std::string::const_iterator, vc7_1_range_iterator<std::string const>::type>));
        std::string const rng("01234567");
        BOOST_CHECK( my_begin(rng) == rng.begin() );
        BOOST_MPL_ASSERT((boost::is_same<std::string::const_iterator, vc7_1_range_iterator<std::string const>::type>));

        vc7_1_range_iterator<std::string const>::type f = my_begin(rng);
        BOOST_CHECK( f == rng.begin() );
    }
}
