#ifndef PSTADE_OVEN_TESTS_HPP
#define PSTADE_OVEN_TESTS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm>
#include <iostream>
#include <boost/assert.hpp>
#include <boost/concept_check.hpp>
#include <boost/foreach.hpp>
#include <boost/noncopyable.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/iterator/new_iterator_tests.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/next_prior.hpp>
#include <pstade/concept.hpp>
#include <pstade/const.hpp>
#include "./algorithm.hpp"
#include "./concepts.hpp"
#include "./copy_range.hpp"
#include "./distance.hpp"
#include "./equals.hpp"
#include "./range_difference.hpp"
#include "./range_iterator.hpp"
#include "./range_reference.hpp"
#include "./range_value.hpp"
#include "./to_sequence.hpp"


namespace pstade { namespace oven {


template< class Range, class Vector >
bool test_SinglePass_Readable(Range& rng, Vector const& expected)
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
    PSTADE_CONCEPT_ASSERT((Readable<Range>));

    if (!oven::equals(rng, expected)) // In fact, Incrementable only.
        return false;

    return true;
}


// Forward
//

namespace tests_detail {


    template< class Range, class Value >
    boost::iterator_range<typename range_iterator<Range>::type> const
    make_removed(Range& rng, Value const& v)
    {
        return boost::iterator_range<typename range_iterator<Range>::type>(
            boost::begin(rng), oven::remove(rng, v)
        );
    }


    template< class Vector > inline
    typename range_value<Vector>::type make_pivot(Vector const& vec)
    {
        BOOST_ASSERT(!boost::empty(vec));
        return vec[oven::distance(vec)/2];
    }


    template< class Range1, class Range2 >
    boost::iterator_range<typename range_iterator<Range1>::type> const
    make_searched(Range1& rng1, Range2 const& rng2)
    {
        return boost::iterator_range<typename range_iterator<Range1>::type>(
            boost::begin(rng1), oven::search(rng1, rng2)
        );
    }


    template< class Vector >
    boost::iterator_range<typename range_iterator<Vector const>::type> const
    make_sub(Vector const& vec)
    {
        typedef typename range_difference<Vector>::type diff_t;
        diff_t d = oven::distance(vec)/3;
        return boost::make_iterator_range(boost::begin(vec) + d, boost::begin(vec) + (2*d));
    }


    template< class Range, class Vector >
    bool forward_r(Range& rng, Vector const& expected)
    {
        PSTADE_CONCEPT_ASSERT((Forward<Range>));
        PSTADE_CONCEPT_ASSERT((Readable<Range>));

        if (!oven::test_SinglePass_Readable(rng, expected))
            return false;

        boost::forward_readable_iterator_test(
            boost::begin(rng), boost::next(boost::begin(rng)),
            expected[0], expected[1]
        );

        if (!oven::equals(
            tests_detail::make_searched(rng,      tests_detail::make_sub(expected)),
            tests_detail::make_searched(expected, tests_detail::make_sub(expected))))
            return false;

        return true;
    };


    template< class Range, class Vector >
    bool forward_rw(Range& rng, Vector const& expected)
    {
        PSTADE_CONCEPT_ASSERT((Writable<Range>));

        Vector exp = expected;
        if (!oven::equals(
                tests_detail::make_removed(rng, tests_detail::make_pivot(expected)),
                tests_detail::make_removed(exp, tests_detail::make_pivot(expected))))
            return false;

        oven::copy(expected, boost::begin(rng)); // restore
        return true;
    }


} // namespace tests_detail


template< class Range, class Vector >
bool test_Forward_Readable(Range& rng, Vector const& expected)
{
    BOOST_ASSERT(oven::distance(expected) >= 3);
    BOOST_ASSERT(oven::distance(rng) == oven::distance(expected));

    {
        if (!tests_detail::forward_r(rng, expected))
            return false;

        std::cout << "Forward Readable Range test passed." << std::endl;
    }

    {
        if (!tests_detail::forward_r(rng|const_qualified, expected))
            return false;

        std::cout << "Forward Readable Range const-qualified test passed." << std::endl;
    }

    return true;
}


template< class Range, class Vector >
bool test_Forward_Readable_Writable(Range& rng, Vector const& expected)
{
    BOOST_ASSERT(oven::distance(expected) >= 3);
    BOOST_ASSERT(oven::distance(rng) == oven::distance(expected));

    if (!oven::test_Forward_Readable(rng, expected))
        return false;

    {
        if (!tests_detail::forward_rw(rng, expected))
            return false;

        std::cout << "Forward Readable Writable Range test passed." << std::endl;
    }

    return true;
}


// Bidirectional
//

namespace tests_detail {


    template< class Range >
    boost::iterator_range<
        boost::reverse_iterator<typename range_iterator<Range>::type>
    > const
    make_reversed(Range& rng)
    {
        return boost::make_iterator_range(
            boost::make_reverse_iterator(boost::end(rng)),
            boost::make_reverse_iterator(boost::begin(rng))
        );
    }


    template< class Value >
    struct less_than
    {
        typedef bool result_type;

        template< class X >
        bool operator()(X const& x) const
        {
            return x < m_v;
        }

        explicit less_than(Value const& v) :
            m_v(v)
        { }

    private:
        Value m_v;
    };

    template< class Value > inline
    less_than<Value> make_less_than(Value const& v)
    {
        return less_than<Value>(v);
    }


    template< class Range, class Vector >
    bool bidirectional_r(Range& rng, Vector const& expected)
    {
        PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
        PSTADE_CONCEPT_ASSERT((Readable<Range>));

        if (!oven::test_Forward_Readable(rng, expected))
            return false;

        boost::bidirectional_readable_iterator_test(
            boost::begin(rng),
            expected[0], expected[1]
        );

        // Todo: add good test here
        //

        return true;
    }


    template< class Range, class Vector >
    bool bidirectional_rw(Range& rng, Vector const& expected)
    {
        PSTADE_CONCEPT_ASSERT((Writable<Range>));

        if (!oven::test_Forward_Readable_Writable(rng, expected))
            return false;

        Vector exp = expected;
        oven::stable_partition(exp, tests_detail::make_less_than(tests_detail::make_pivot(expected)));
        oven::stable_partition(rng, tests_detail::make_less_than(tests_detail::make_pivot(expected)));
        if (!oven::equals(rng, exp)) // strictly speaking, can fail :-)
            return false;

        oven::copy(expected, boost::begin(rng)); // restore
        return true;
    }


} // namespace tests_detail


template< class Range, class Vector >
bool test_Bidirectional_Readable(Range& rng, Vector const& expected)
{
    BOOST_ASSERT(oven::distance(expected) >= 3);
    BOOST_ASSERT(oven::distance(rng) == oven::distance(expected));

    {
        if (!tests_detail::bidirectional_r(rng, expected))
            return false;

        Vector expRev = expected;
        oven::reverse(expRev); // vector needed instead iterator_range.
        if (!tests_detail::bidirectional_r(tests_detail::make_reversed(rng), expRev))
            return false;

        std::cout << "Bidirectional Readable Range test passed." << std::endl;
    }

    {
        if (!tests_detail::bidirectional_r(rng|const_qualified, expected))
            return false;

        Vector expRev = expected;
        oven::reverse(expRev);
        if (!tests_detail::bidirectional_r(tests_detail::make_reversed(rng|const_qualified), expRev))
            return false;

        std::cout << "Bidirectional Readable Range const-qualified test passed." << std::endl;
    }

    return true;
}


template< class Range, class Vector >
bool test_Bidirectional_Readable_Writable(Range& rng, Vector const& expected)
{
    BOOST_ASSERT(oven::distance(expected) >= 3);
    BOOST_ASSERT(oven::distance(rng) == oven::distance(expected));

    if (!oven::test_Bidirectional_Readable(rng, expected))
        return false;

    {
        if (!tests_detail::bidirectional_rw(rng, expected))
            return false;

        Vector expRev = expected;
        oven::reverse(expRev);
        if (!tests_detail::bidirectional_rw(tests_detail::make_reversed(rng), expRev))
            return false;

        std::cout << "Bidirectional Readable Writable Range test passed." << std::endl;
    }

    return true;
}


// RandomAccess
//

namespace tests_detail {


    template< class Range, class Vector >
    bool random_access_r(Range& rng, Vector const& expected)
    {
        PSTADE_CONCEPT_ASSERT((RandomAccess<Range>));
        PSTADE_CONCEPT_ASSERT((Readable<Range>));

        if (!oven::test_Bidirectional_Readable(rng, expected))
            return false;

        boost::random_access_readable_iterator_test(
            boost::begin(rng), static_cast<int>(oven::distance(expected)), expected
        );

        return true;
    }


    template< class Range, class Vector >
    bool random_access_rw(Range& rng, Vector const& expected)
    {
        PSTADE_CONCEPT_ASSERT((Writable<Range>));

        if (!oven::test_Bidirectional_Readable_Writable(rng, expected))
            return false;

        Vector exp = expected;

        oven::sort(exp);
        oven::sort(rng);
        if (!oven::equals(rng, exp))
            return false;

        oven::random_shuffle(exp);
        oven::random_shuffle(rng);
        oven::stable_sort(exp);
        oven::stable_sort(rng);
        if (!oven::equals(rng, exp))
            return false;

        oven::copy(expected, boost::begin(rng)); // restore
        return true;
    }


} // namespace tests_detail


template< class Range, class Vector >
bool test_RandomAccess_Readable(Range& rng, Vector const& expected)
{
    BOOST_ASSERT(oven::distance(expected) >= 3);
    BOOST_ASSERT(oven::distance(rng) == oven::distance(expected));

    {
        if (!tests_detail::random_access_r(rng, expected))
            return false;

        Vector expRev = expected;
        oven::reverse(expRev);
        if (!tests_detail::random_access_r(tests_detail::make_reversed(rng), expRev))
            return false;

        std::cout << "RandomAccess Readable Range test passed." << std::endl;
    }

    {
        if (!tests_detail::random_access_r(rng|const_qualified, expected))
            return false;

        Vector expRev = expected;
        oven::reverse(expRev);
        if (!tests_detail::random_access_r(tests_detail::make_reversed(rng|const_qualified), expRev))
            return false;

        std::cout << "RandomAccess Readable Range const-qualified test passed." << std::endl;
    }

    return true;
}


template< class Range, class Vector >
bool test_RandomAccess_Readable_Writable(Range& rng, Vector const& expected)
{
    BOOST_ASSERT(oven::distance(expected) >= 3);
    BOOST_ASSERT(oven::distance(rng) == oven::distance(expected));

    if (!oven::test_RandomAccess_Readable(rng, expected))
        return false;

    {
        if (!tests_detail::random_access_rw(rng, expected))
            return false;

        Vector expRev = expected;
        oven::reverse(expRev);
        if (!tests_detail::random_access_rw(tests_detail::make_reversed(rng), expRev))
            return false;

        std::cout << "RandomAccess Readable Writable Range test passed." << std::endl;
    }

    return true;
}


// Misc
//

template< class Range >
bool test_empty(Range& rng)
{
    if(!boost::empty(rng))
        return false;

    return true;
}


template< class To, class From >
bool test_Copyable(From const& from)
{
    PSTADE_CONCEPT_ASSERT((boost::CopyConstructible<To>));

    To to = from|copied;

    if (!oven::equals(from, oven::copy_range<To>(from)))
        return false;

    if (!oven::equals(from, to))
        return false;

    return true;
}


} } // namespace pstade::oven


#endif
