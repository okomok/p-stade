#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/constants.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <string>
#include <vector>
#include <boost/range.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/oven/identities.hpp>
#include <pstade/egg/is_same.hpp>
#include <boost/iterator.hpp>
#include <pstade/oven/equals.hpp>


namespace lambda = boost::lambda;
namespace oven = pstade::oven;
using namespace oven;



template<class V, class R>
struct an_iterator :
    boost::iterator<
        std::forward_iterator_tag, V, std::ptrdiff_t, V const*, R
    >
{ };


// lvalue
BOOST_MPL_ASSERT((boost::is_same<int const&, detail::constant_reference< an_iterator<int, int&> >::type>));
BOOST_MPL_ASSERT((boost::is_same<int const&, detail::constant_reference< an_iterator<int, int const&> >::type>));

// readable
BOOST_MPL_ASSERT((boost::is_same<int const, detail::constant_reference< an_iterator <int, int> >::type>));
BOOST_MPL_ASSERT((boost::is_same<int const, detail::constant_reference< an_iterator<int, int const> >::type>));
BOOST_MPL_ASSERT((boost::is_same<int const, detail::constant_reference< an_iterator<int, char&> >::type>));
BOOST_MPL_ASSERT((boost::is_same<char const, detail::constant_reference< an_iterator<char, int&> >::type>));
BOOST_MPL_ASSERT((boost::is_same<int const, detail::constant_reference< an_iterator<int, char const&> >::type>));
BOOST_MPL_ASSERT((boost::is_same<char const, detail::constant_reference< an_iterator<char, int const&> >::type>));
BOOST_MPL_ASSERT((boost::is_same<int const, detail::constant_reference< an_iterator<int, char const> >::type>));
BOOST_MPL_ASSERT((boost::is_same<char const, detail::constant_reference< an_iterator<char, int const> >::type>));
BOOST_MPL_ASSERT((boost::is_same<int const, detail::constant_reference< an_iterator<int, char> >::type>));
BOOST_MPL_ASSERT((boost::is_same<char const, detail::constant_reference< an_iterator<char, int> >::type>));



// Assume you want to keep 'rng' from
// unintentional modifications.

template< class Range >
void legacy_way(Range const& rng)
{
    *boost::begin(rng) = 'x';
    *boost::const_begin(rng) = 'x';
}

template< class Range >
void modern_way(Range& rng)
{
    typename pstade::result_of<T_make_constants(Range&)>::type safe_rng
        = make_constants(rng);
    *boost::begin(safe_rng) = 'x';
}

#if 0
void test_iterator()
{
    std::string rng("abc");
    std::string::iterator it = boost::begin(rng);
    constant_iterator<std::string::iterator> cit = it;
    BOOST_CHECK( cit == it );
    BOOST_CHECK( *cit == 'a' );
}
#endif


void pstade_minimal_test()
{
    {
        std::string str("hello, constant_range!");
        BOOST_CHECK(equals(str, str|constants));
        ::legacy_way(str|identities); // oops, compiles.
        // ::modern_way(str|identities); // error
        // ::legacy_way(str|identities|constants); // error
    }
    {
        int a[] = { 6,4,2,3,6,3,8,5,1,4,6,8,3,1 };
        int b[] = { 6,4,2,3,6,3,8,5,1,4,6,8,3,1 };
        test::adaptor_random_access_constant_int(lambda::bind(make_constants, lambda::_1), a, b);
        BOOST_CHECK( equals(a, a|constants, pstade::egg::is_same) );
    }
}
