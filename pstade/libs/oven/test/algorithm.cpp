#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/algorithm.hpp>
#include <pstade/oven/begin_end.hpp>


//  (C) Copyright Eric Niebler 2004.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/*
 Revision history:
   13 December 2004 : Initial version.
*/


#include <cstdlib>
#include <set>
#include <list>
#include <vector>
#include <iterator>
#include <functional>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/range.hpp>


using namespace pstade;
using namespace oven;


///////////////////////////////////////////////////////////////////////////////
// dummy function object, used with algorithms
//
struct null_fun
{
    template<typename T>
        void operator()(T const &t) const
    {
        (void)t; // unused;
    }
};

///////////////////////////////////////////////////////////////////////////////
// dummy predicate, used with algorithms
//
struct null_pred
{
    template<typename T>
    bool operator()(T const &t) const
    {
        return t == T();
    }
};

///////////////////////////////////////////////////////////////////////////////
// dummy unary op, used with algorithms
//
struct null_op1
{
    template<typename T>
    T const & operator()(T const & t) const
    {
        return t;
    }
};

///////////////////////////////////////////////////////////////////////////////
// dummy binary op, used with algorithms
//
struct null_op2
{
    template<typename T,typename U>
    T const & operator()(T const & t, U const & u) const
    {
        (void)u; // unused;
        return t;
    }
};

template<typename Rng>
void test_random_algorithms(Rng & rng, std::random_access_iterator_tag)
{
    typedef BOOST_DEDUCED_TYPENAME boost::range_result_iterator<Rng>::type iterator;
    typedef BOOST_DEDUCED_TYPENAME boost::range_value<Rng>::type value_type;
    typedef BOOST_DEDUCED_TYPENAME boost::range_size<Rng>::type size_type;
    typedef BOOST_DEDUCED_TYPENAME boost::iterator_category<iterator>::type iterator_category;

    // just make sure these compile (for now)
    bool zero = false;
    if(zero)
    {
        oven::random_shuffle(rng);
        oven::random_shuffle(rng, null_op1());

        oven::sort(rng);
        oven::sort(rng, std::less<value_type>());

        oven::stable_sort(rng);
        oven::stable_sort(rng, std::less<value_type>());

        oven::partial_sort(rng, oven::begin(rng));
        oven::partial_sort(rng, oven::begin(rng), std::less<value_type>());

        oven::nth_element(rng, oven::begin(rng));
        oven::nth_element(rng, oven::begin(rng), std::less<value_type>());

        oven::push_heap(rng);
        oven::push_heap(rng, std::less<value_type>());

        oven::pop_heap(rng);
        oven::pop_heap(rng, std::less<value_type>());

        oven::make_heap(rng);
        oven::make_heap(rng, std::less<value_type>());

        oven::sort_heap(rng);
        oven::sort_heap(rng, std::less<value_type>());
    }
}

template<typename Rng>
void test_random_algorithms(Rng & rng, std::input_iterator_tag)
{
    (void)rng; // unused
    // no-op
}

template<typename Rng>
void test_algorithms(Rng & rng)
{
    typedef BOOST_DEDUCED_TYPENAME boost::range_result_iterator<Rng>::type iterator;
    typedef BOOST_DEDUCED_TYPENAME boost::range_value<Rng>::type value_type;
    typedef BOOST_DEDUCED_TYPENAME boost::range_size<Rng>::type size_type;
    typedef BOOST_DEDUCED_TYPENAME boost::iterator_category<iterator>::type iterator_category;

    // just make sure these compile (for now)
    bool zero = 0;
    if(zero)
    {
        value_type val = value_type();

        value_type rng2[] = {value_type(),value_type(),value_type()};
        typedef value_type* iterator2;

        value_type out[100] = {};
        typedef value_type* out_iterator;

        null_fun f = null_fun();
        iterator i = iterator();
        bool b = bool();
        out_iterator o = out_iterator();
        size_type s = size_type();

        f = oven::for_each(rng, null_fun());

        i = oven::find(rng, val);
        i = oven::find_if(rng, null_pred());

        i = oven::find_end(rng, rng2);
        i = oven::find_end(rng, rng2, std::equal_to<value_type>());

        i = oven::find_first_of(rng, rng2);
        i = oven::find_first_of(rng, rng2, std::equal_to<value_type>());

        i = oven::adjacent_find(rng);
        i = oven::adjacent_find(rng, std::equal_to<value_type>());

        s = oven::count(rng, val);
        s = oven::count_if(rng, null_pred());

        std::pair<iterator,iterator2> p1;
        p1 = oven::mismatch(rng, oven::begin(rng2));
        p1 = oven::mismatch(rng, oven::begin(rng2),std::equal_to<value_type>());

        b = oven::equal(rng, oven::begin(rng2));
        b = oven::equal(rng, oven::begin(rng2),std::equal_to<value_type>());

        i = oven::search(rng, rng2);
        i = oven::search(rng, rng2, std::equal_to<value_type>());

        o = oven::copy(rng, oven::begin(out));
        o = oven::copy_backward(rng, oven::end(out));

        o = oven::transform(rng, oven::begin(out), null_op1());
        o = oven::transform(rng, oven::begin(rng2), oven::begin(out), null_op2());

        oven::replace(rng, val, val);
        oven::replace_if(rng, null_pred(), val);

        o = oven::replace_copy(rng, oven::begin(out), val, val);
        o = oven::replace_copy_if(rng, oven::begin(out), null_pred(), val);

        oven::fill(rng, val);
        oven::fill_n(rng, boost::size(rng), val);

        oven::generate(rng, &std::rand);
        oven::generate_n(rng, boost::size(rng), &std::rand);

        i = oven::remove(rng, val);
        i = oven::remove_if(rng, null_pred());

        o = oven::remove_copy(rng, oven::begin(out), val);
        o = oven::remove_copy_if(rng, oven::begin(out), null_pred());

        i = oven::unique(rng);
        i = oven::unique(rng, std::equal_to<value_type>());

        o = oven::unique_copy(rng, oven::begin(out));
        o = oven::unique_copy(rng, oven::begin(out), std::equal_to<value_type>());

        oven::reverse(rng);

        o = oven::reverse_copy(rng, oven::begin(out));

        oven::rotate(rng, oven::begin(rng));

        o = oven::rotate_copy(rng, oven::begin(rng), oven::begin(out));

        i = oven::partition(rng, null_pred());
        i = oven::stable_partition(rng, null_pred());

        o = oven::partial_sort_copy(rng, out);
        o = oven::partial_sort_copy(rng, out, std::less<value_type>());

        i = oven::lower_bound(rng, val);
        i = oven::lower_bound(rng, val, std::less<value_type>());

        i = oven::upper_bound(rng, val);
        i = oven::upper_bound(rng, val, std::less<value_type>());

        std::pair<iterator,iterator> p2;
        p2 = oven::equal_range(rng, val);
        p2 = oven::equal_range(rng, val, std::less<value_type>());

        b = oven::binary_search(rng, val);
        b = oven::binary_search(rng, val, std::less<value_type>());

        oven::inplace_merge(rng, oven::begin(rng));
        oven::inplace_merge(rng, oven::begin(rng), std::less<value_type>());

        b = oven::includes(rng, rng2);
        b = oven::includes(rng, rng2, std::equal_to<value_type>());

        o = oven::set_union(rng, rng2, oven::begin(out));
        o = oven::set_union(rng, rng2, oven::begin(out), std::equal_to<value_type>());

        o = oven::set_intersection(rng, rng2, oven::begin(out));
        o = oven::set_intersection(rng, rng2, oven::begin(out), std::equal_to<value_type>());

        o = oven::set_difference(rng, rng2, oven::begin(out));
        o = oven::set_difference(rng, rng2, oven::begin(out), std::equal_to<value_type>());

        o = oven::set_symmetric_difference(rng, rng2, oven::begin(out));
        o = oven::set_symmetric_difference(rng, rng2, oven::begin(out), std::equal_to<value_type>());

        i = oven::min_element(rng);
        i = oven::min_element(rng, std::less<value_type>());

        i = oven::max_element(rng);
        i = oven::max_element(rng, std::less<value_type>());

        b = oven::lexicographical_compare(rng, rng);
        b = oven::lexicographical_compare(rng, rng, std::equal_to<value_type>());

        b = oven::next_permutation(rng);
        b = oven::next_permutation(rng, std::less<value_type>());

        b = oven::prev_permutation(rng);
        b = oven::prev_permutation(rng, std::less<value_type>());
    }

    // test the algorithms that require a random-access range
    test_random_algorithms(rng, iterator_category());
}

int* addr(int &i) { return &i; }
bool true_(int) { return true; }

///////////////////////////////////////////////////////////////////////////////
// test_main
//   
int test_main( int, char*[] )
{
    // int_iterator
    typedef ::boost::counting_iterator<int> int_iterator;

    // define come containers
    char ntcs_buffer[] = "\1\2\3\4\5";
    char *ntcs  = ntcs_buffer;
    int array[] = { 1,2,3,4,5 };
    std::list<int> my_list(int_iterator(1),int_iterator(6));
    std::vector<int> my_vector(int_iterator(1),int_iterator(6));
    std::pair<std::vector<int>::iterator,std::vector<int>::iterator> my_pair(my_vector.begin(),my_vector.end());

    // test the algorithms with list and const list
    test_algorithms(ntcs);
    test_algorithms(array);
    test_algorithms(my_list);
    test_algorithms(my_vector);
    test_algorithms(my_pair);

    return 0;
}
