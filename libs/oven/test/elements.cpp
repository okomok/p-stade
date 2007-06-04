#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/version.hpp>
#if BOOST_VERSION >= 103500


#include <pstade/oven/elements.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


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


rng_t make_b()
{
    ::rng_t b;
    b.push_back( boost::fusion::make_tuple(5, 'a') );
    b.push_back( boost::fusion::make_tuple(1, 'b') );
    b.push_back( boost::fusion::make_tuple(3, 'b') );
    b.push_back( boost::fusion::make_tuple(45, 'a') );
    b.push_back( boost::fusion::make_tuple(63, 'b') );
    b.push_back( boost::fusion::make_tuple(1, 'a') );
    b.push_back( boost::fusion::make_tuple(1, 'b') );
    b.push_back( boost::fusion::make_tuple(7, 'a') );
    b.push_back( boost::fusion::make_tuple(4, 'b') );
    b.push_back( boost::fusion::make_tuple(2, 'a') );
    b.push_back( boost::fusion::make_tuple(1, 'b') );
    return b;
};


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int a[] = { 5,1,3,45,63,1,1,7,4,2,1 };
        ::rng_t b = ::make_b();
        test::random_access_constant(b|elements_c<0>(), a);
        test::random_access_constant(b|const_refs|elements_c<0>(), a);
        test::random_access_swappable(b|elements_c<0>(), a);
    }

#if !BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))
    // fustion::vector over-optimistic template constructor breaks down 'oven::read'.
    // No way to copyconstruct fustion::vector from proxy under msvc.
    {
        int a[] = { 5,1,3,45,63,1,1,7,4,2,1 };
        ::rng_t b = ::make_b();
        test::random_access_constant(b|test::proxies|elements_c<0>()|const_refs, a);
    }
#endif
}

#else

void pstade_minimal_test()
{ }

#endif //  BOOST_VERSION >= 103500
