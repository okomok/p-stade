#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/detail/boost_begin_end.hpp> // for Boost1.33 'const_begin' ADL bug.


#include <pstade/oven/tests.hpp>
#include <pstade/oven/constants.hpp>
// #include <pstade/oven/constant_iterator.hpp>


#include <string>
#include <vector>
#include <boost/range.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include "./core.hpp"
#include <pstade/oven/identities.hpp>
#include <pstade/is_same.hpp>
#include <boost/iterator.hpp>


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
    typename boost::result_of<op_make_constants(Range&)>::type safe_rng
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


void test()
{
    {
        std::string str("hello, constant_range!");
        BOOST_CHECK(oven::equals(str, str|constants));
        ::legacy_way(str|identities); // oops, compiles.
        // ::modern_way(str|identities); // error
        // ::legacy_way(str|identities|constants); // error
    }
    {
        std::string rng("urifoqjfoqnfeionfqo");
        std::vector<char> expected = rng|copied;
        BOOST_CHECK(oven::test_RandomAccess_Readable(rng, expected));
        BOOST_CHECK( equals(rng, rng|constants, pstade::is_same) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
