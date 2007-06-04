#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/concatenated.hpp>
#include <pstade/unit_test.hpp>
#include "./detail/test.hpp"


#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <pstade/oven/reversed.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/rvalues.hpp>


#include <pstade/biscuit/parser.hpp>
#include <pstade/biscuit/range/token_range.hpp>


namespace lambda = boost::lambda;
namespace oven = pstade::oven;
using namespace oven;


void test_nc_nc()
{
    std::vector<int> l0; // empty
    int l1[] = { 6,1,3,6 };
    int l2[] = { 4 };
    int l3[] = { 3,2 };
    int l4[] = { 7 };
    int l5[] = { 8 };
    int l6[] = { 3,1,2,9,7 };
    int l7[] = { 56,1,3 };
    int l8[] = { 7,1 };
    int l9[] = { 17 };

    typedef boost::ptr_vector<test::ncint> local_rng_t; // noncopyable-noncopyable

    int a[] = { 6,1,3,6,   4,   3,2,   7,   8,   3,1,2,9,7,  56,1,3,  7,1,  17    };

    boost::ptr_vector<local_rng_t> b; {
        b.push_back(test::new_vector<test::ncint>(l0));
        b.push_back(test::new_vector<test::ncint>(l1));
        b.push_back(test::new_vector<test::ncint>(l0));
        b.push_back(test::new_vector<test::ncint>(l2));
        b.push_back(test::new_vector<test::ncint>(l3));
        b.push_back(test::new_vector<test::ncint>(l4));
        b.push_back(test::new_vector<test::ncint>(l0));
        b.push_back(test::new_vector<test::ncint>(l0));
        b.push_back(test::new_vector<test::ncint>(l5));
        b.push_back(test::new_vector<test::ncint>(l6));
        b.push_back(test::new_vector<test::ncint>(l7));
        b.push_back(test::new_vector<test::ncint>(l8));
        b.push_back(test::new_vector<test::ncint>(l0));
        b.push_back(test::new_vector<test::ncint>(l9));
        b.push_back(test::new_vector<test::ncint>(l0));
    }

    test::bidirectional_swappable(b|concatenated, *test::new_vector<test::ncint>(a));
}


void test_c_nc()
{
    std::vector<int> l0; // empty
    int l1[] = { 6,1,3,6 };
    int l2[] = { 4 };
    int l3[] = { 3,2 };
    int l4[] = { 7 };
    int l5[] = { 8 };
    int l6[] = { 3,1,2,9,7 };
    int l7[] = { 56,1,3 };
    int l8[] = { 7,1 };
    int l9[] = { 17 };

    typedef boost::ptr_vector<int> local_rng_t; // copyable-noncopyable

    int a[] = { 6,1,3,6,   4,   3,2,   7,   8,   3,1,2,9,7,  56,1,3,  7,1,  17    };

    boost::ptr_vector<local_rng_t> b; {
        b.push_back(test::new_vector<int>(l0));
        b.push_back(test::new_vector<int>(l1));
        b.push_back(test::new_vector<int>(l0));
        b.push_back(test::new_vector<int>(l2));
        b.push_back(test::new_vector<int>(l3));
        b.push_back(test::new_vector<int>(l4));
        b.push_back(test::new_vector<int>(l0));
        b.push_back(test::new_vector<int>(l0));
        b.push_back(test::new_vector<int>(l5));
        b.push_back(test::new_vector<int>(l6));
        b.push_back(test::new_vector<int>(l7));
        b.push_back(test::new_vector<int>(l8));
        b.push_back(test::new_vector<int>(l0));
        b.push_back(test::new_vector<int>(l9));
        b.push_back(test::new_vector<int>(l0));
    }

    test::bidirectional_constant(b|concatenated, a);
    test::bidirectional_swappable(b|concatenated, a);
}


template< class V, class Range >
std::vector<V>
make_vector(Range const& rng)
{
    std::vector<V> c;
    std::copy(boost::begin(rng), boost::end(rng), std::back_inserter(c));
    return c;
}


template< class BeforeFun >
void test_iter_range_range(BeforeFun f)
{
    typedef std::vector<int> src_local_rng_t;

    int l1[] = { 6,1,3,6 };
    int l2[] = { 4 };
    int l3[] = { 3,2 };
    int l4[] = { 7 };
    int l5[] = { 8 };
    int l6[] = { 3,1,2,9,7 };
    int l7[] = { 56,1,3 };
    int l8[] = { 7,1 };
    int l9[] = { 17 };

    src_local_rng_t sl0; // empty
    src_local_rng_t sl1 = ::make_vector<int>(l1);
    src_local_rng_t sl2 = ::make_vector<int>(l2);
    src_local_rng_t sl3 = ::make_vector<int>(l3);
    src_local_rng_t sl4 = ::make_vector<int>(l4);
    src_local_rng_t sl5 = ::make_vector<int>(l5);
    src_local_rng_t sl6 = ::make_vector<int>(l6);
    src_local_rng_t sl7 = ::make_vector<int>(l7);
    src_local_rng_t sl8 = ::make_vector<int>(l8);
    src_local_rng_t sl9 = ::make_vector<int>(l9);

    typedef iter_range_of<src_local_rng_t>::type local_rng_t; // iterator-range

    int a[] = { 6,1,3,6,   4,   3,2,   7,   8,   3,1,2,9,7,  56,1,3,  7,1,  17    };

    std::vector<local_rng_t> b; {
        b.push_back(make_iter_range(sl0));
        b.push_back(make_iter_range(sl1));
        b.push_back(make_iter_range(sl0));
        b.push_back(make_iter_range(sl2));
        b.push_back(make_iter_range(sl3));
        b.push_back(make_iter_range(sl4));
        b.push_back(make_iter_range(sl0));
        b.push_back(make_iter_range(sl0));
        b.push_back(make_iter_range(sl5));
        b.push_back(make_iter_range(sl6));
        b.push_back(make_iter_range(sl7));
        b.push_back(make_iter_range(sl8));
        b.push_back(make_iter_range(sl0));
        b.push_back(make_iter_range(sl9));
        b.push_back(make_iter_range(sl0));
    }

    test::bidirectional_constant(f(b)|concatenated, a);
    test::bidirectional_swappable(f(b)|concatenated, a);
}


void pstade_unit_test()
{
    ::test_nc_nc();
    ::test_c_nc();
    ::test_iter_range_range(pstade::identity);
    ::test_iter_range_range(lambda::bind(make_const_refs,    lambda::_1));
    ::test_iter_range_range(lambda::bind(make_rvalues,       lambda::_1));
    ::test_iter_range_range(lambda::bind(test::make_proxies, lambda::_1));

    {
        namespace biscuit = pstade::biscuit;

        typedef biscuit::seq<
            biscuit::chseq<'/','*'>,
            biscuit::star_until< biscuit::any, biscuit::chseq<'*','/'> >
        > c_comment;

        std::string rng(" /*hello*/ abc /* xx*/ ii /*312  */ ");
        std::vector<char> expected = std::string("/*hello*//* xx*//*312  */")|copied;

        // It seems not ForwardWritable, because once you change
        // a character, the parsing way is changed.
        // If it is a SinglePass algorithm, it seems to be writable, though.
        test::forward_constant(
            rng|biscuit::tokenized<c_comment>()|concatenated,
            expected
        );
    }
}
