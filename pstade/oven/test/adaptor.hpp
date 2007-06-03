#ifndef PSTADE_OVEN_TEST_ADAPTOR_HPP
#define PSTADE_OVEN_TEST_ADAPTOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License)( Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../detail/prelude.hpp"
#include "./bidirectional.hpp"
#include "./emptiness.hpp"
#include "./forward.hpp"
#include "./new_list.hpp"
#include "./new_vector.hpp"
#include "./ncint.hpp"
#include "./proxies.hpp"
#include "./random_access.hpp"
#include "./single_pass.hpp"

#if !defined(PSTADE_OVEN_TEST_CONST_REFS)
#include "../const_refs.hpp"
#endif

// inclusion guaranteed
#include <boost/lambda/bind.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/ref.hpp>


namespace pstade { namespace oven { namespace test {


template< class F, class RangeA, class RangeB >
void adaptor_single_pass_readable_int(F f, RangeA const& rngA, RangeB& rngB)
{
    test::single_pass_readable(f(rngB), rngA);
#if !defined(PSTADE_OVEN_TEST_CONST_REFS)
    test::single_pass_readable(f(make_const_refs(rngB)), rngA);
#endif
    test::single_pass_readable(f(make_proxies(rngB)), rngA);
}


template< class F, class RangeA, class RangeB >
void adaptor_forward_constant_int(F f, RangeA const& rngA, RangeB& rngB)
{
    test::forward_constant(f(rngB), rngA);
#if !defined(PSTADE_OVEN_TEST_CONST_REFS)
    test::forward_constant(f(make_const_refs(rngB)), rngA);
#endif
}


template< class F, class RangeA, class RangeB >
void adaptor_forward_swappable_int(F f, RangeA const& rngA, RangeB& rngB)
{
    test::forward_swappable(f(*test::new_list<int>(rngB)), rngA);
    test::forward_swappable(f(test::make_proxies(*test::new_list<int>(rngB))), rngA);
    test::forward_swappable(f(*test::new_list<ncint>(rngB)), *test::new_list<ncint>(rngA));
}


template< class F, class RangeA, class RangeB >
void adaptor_bidirectional_constant_int(F f, RangeA const& rngA, RangeB& rngB)
{
    test::bidirectional_constant(f(rngB), rngA);
#if !defined(PSTADE_OVEN_TEST_CONST_REFS)
    test::bidirectional_constant(f(make_const_refs(rngB)), rngA);
#endif
}


template< class F, class RangeA, class RangeB >
void adaptor_bidirectional_swappable_int(F f, RangeA const& rngA, RangeB& rngB)
{
    test::bidirectional_swappable(f(*test::new_list<int>(rngB)), rngA);
    test::bidirectional_swappable(f(test::make_proxies(*test::new_list<int>(rngB))), rngA);
    test::bidirectional_swappable(f(*test::new_list<ncint>(rngB)), *test::new_list<ncint>(rngA));
}


template< class F, class RangeA, class RangeB >
void adaptor_random_access_constant_int(F f, RangeA const& rngA, RangeB& rngB)
{
    test::random_access_constant(f(rngB), rngA);
#if !defined(PSTADE_OVEN_TEST_CONST_REFS)
    test::random_access_constant(f(make_const_refs(rngB)), rngA);
#endif
}


template< class F, class RangeA, class RangeB >
void adaptor_random_access_swappable_int(F f, RangeA const& rngA, RangeB& rngB)
{
    test::random_access_swappable(f(*test::new_vector<int>(rngB)), rngA);
    test::random_access_swappable(f(test::make_proxies(*test::new_vector<int>(rngB))), rngA);
    test::random_access_swappable(f(*test::new_vector<ncint>(rngB)), *test::new_vector<ncint>(rngA));
}


template< class F >
void adaptor_emptiness_int(F f)
{
    test::emptiness(f(*test::new_vector0<int>()));
}


} } } // namespace pstade::oven::test


#endif
