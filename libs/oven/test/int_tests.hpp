#ifndef PSTADE_LIBS_OVEN_TEST_INT_TESTS_HPP
#define PSTADE_LIBS_OVEN_TEST_INT_TESTS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/test/test.hpp>


namespace oven = pstade::oven;
using namespace oven;


#define PSTADE_sr(Ad, A, B) \
    test::single_pass_readable(B|Ad, A); \
    test::single_pass_readable(B|const_refs|Ad, A); \
    test::single_pass_readable(B|test::proxies|Ad, A); \
/**/


#define PSTADE_fc(Ad, A, B) \
    test::forward_constant(B|Ad, A); \
    test::forward_constant(B|const_refs|Ad, A); \
/**/


#define PSTADE_fs(Ad, A, B) \
    test::forward_swappable(*test::new_list<int>(B)|Ad, A); \
    test::forward_swappable(*test::new_list<int>(B)|test::proxies|Ad, A); \
    test::forward_swappable(*test::new_list<test::ncint>(B)|Ad, *test::new_list<test::ncint>(A)); \
/**/


#define PSTADE_bc(Ad, A, B) \
    test::bidirectional_constant(B|Ad, A); \
    test::bidirectional_constant(B|const_refs|Ad, A); \
/**/


#define PSTADE_bs(Ad, A, B) \
    test::bidirectional_swappable(*test::new_list<int>(B)|Ad, A); \
    test::bidirectional_swappable(*test::new_list<int>(B)|test::proxies|Ad, A); \
    test::bidirectional_swappable(*test::new_list<test::ncint>(B)|Ad, *test::new_list<test::ncint>(A)); \
/**/


#define PSTADE_rc(Ad, A, B) \
    test::random_access_constant(B|Ad, A); \
    test::random_access_constant(B|const_refs|Ad, A); \
/**/


#define PSTADE_rs(Ad, A, B) \
    test::random_access_swappable(*test::new_vector<int>(B)|Ad, A); \
    test::random_access_swappable(*test::new_vector<int>(B)|test::proxies|Ad, A); \
    test::random_access_swappable(*test::new_vector<test::ncint>(B)|Ad, *test::new_vector<test::ncint>(A)); \
/**/


// Empty Forward
#define PSTADE_ef(Ad) \
    test::emptiness(*test::new_vector0<int>()|Ad); \
    test::emptiness(*test::new_vector0<test::ncint>()|Ad); \
/**/


// Empty SinglePass
#define PSTADE_es(Ad) \
    test::emptiness(*test::new_vector0<int>()|identities(in_single_pass)|Ad); \
/**/


#endif
