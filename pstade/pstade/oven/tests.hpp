#ifndef PSTADE_OVEN_TESTS_HPP
#define PSTADE_OVEN_TESTS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(PSTADE_CONCEPT_CHECK) \
    && !defined(PSTADE_OVEN_TESTS_NO_CONCEPT_CHECK)
#define PSTADE_CONCEPT_CHECK
#endif


#include <algorithm>
#include <boost/assert.hpp>
#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/iterator/new_iterator_tests.hpp>
#include <boost/next_prior.hpp>
#include <pstade/reference.hpp>
#include "./algorithm.hpp"
#include "./concepts.hpp"
#include "./distance.hpp"
#include "./equals.hpp"
#include "./range_difference.hpp"
#include "./range_iterator.hpp"
#include "./range_reference.hpp"
#include "./range_value.hpp"

// you need not include them.
#include <vector>
#include <pstade/concept.hpp>
#include "./copy_range.hpp"


#if !defined(PSTADE_OVEN_TESTS_REVERSE_RANGE_TESTING)
    #include "./reverse_range.hpp"
#else
    #include <boost/iterator/reverse_iterator.hpp> // is broken; see "./reverse_iterator.hpp".
#endif


namespace pstade { namespace oven {


template< class Range, class Vector >
bool test_SinglePass_Readable(Range& rng, Vector const& expected)
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
    PSTADE_CONCEPT_ASSERT((Readable<Range>));

    if (!oven::equals(rng, expected)) { // In fact, Incrementable only.
        BOOST_ASSERT(false);
        return false;
    }

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

        if (!oven::test_SinglePass_Readable(rng, expected)) {
            BOOST_ASSERT(false);
            return false;
        }

        boost::forward_readable_iterator_test(
            boost::begin(rng), boost::next(boost::begin(rng)),
            expected[0], expected[1]
        );

        if (!oven::equals(
            tests_detail::make_searched(rng,      tests_detail::make_sub(expected)),
            tests_detail::make_searched(expected, tests_detail::make_sub(expected)))) {
            BOOST_ASSERT(false);
            return false;
        }

        return true;
    };


    template< class Range, class Vector >
    bool forward_rw(Range& rng, Vector const& expected)
    {
        PSTADE_CONCEPT_ASSERT((Writable<Range>));

        Vector exp = expected;
        if (!oven::equals(
                tests_detail::make_removed(rng, tests_detail::make_pivot(expected)),
                tests_detail::make_removed(exp, tests_detail::make_pivot(expected)))) {
            BOOST_ASSERT(false);
            return false;
        }

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
        if (!tests_detail::forward_r(rng, expected)) {
            BOOST_ASSERT(false);
            return false;
        }
    }

    {
        if (!tests_detail::forward_r(rng|const_referenced, expected)) {
            BOOST_ASSERT(false);
            return false;
        }
    }

    return true;
}


template< class Range, class Vector >
bool test_Forward_Readable_Writable(Range& rng, Vector const& expected)
{
    BOOST_ASSERT(oven::distance(expected) >= 3);
    BOOST_ASSERT(oven::distance(rng) == oven::distance(expected));

    if (!oven::test_Forward_Readable(rng, expected)) {
            BOOST_ASSERT(false);
            return false;
        }

    {
        if (!tests_detail::forward_rw(rng, expected)) {
            BOOST_ASSERT(false);
            return false;
        }
    }

    return true;
}


// Bidirectional
//

namespace tests_detail {


#if !defined(PSTADE_OVEN_TESTS_REVERSE_RANGE_TESTING)
    template< class Range >
    reverse_range<Range> const
    make_reversed(Range& rng)
    {
        return rng|reversed;
    }
#else
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
#endif


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

        if (!oven::test_Forward_Readable(rng, expected)) {
            BOOST_ASSERT(false);
            return false;
        }

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

        if (!oven::test_Forward_Readable_Writable(rng, expected)) {
            BOOST_ASSERT(false);
            return false;
        }

        Vector exp = expected;
        oven::stable_partition(exp, tests_detail::make_less_than(tests_detail::make_pivot(expected)));
        oven::stable_partition(rng, tests_detail::make_less_than(tests_detail::make_pivot(expected)));
        if (!oven::equals(rng, exp)) { // strictly speaking, can fail :-)
            BOOST_ASSERT(false);
            return false;
        }

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
        if (!tests_detail::bidirectional_r(rng, expected)) {
            BOOST_ASSERT(false);
            return false;
        }

        Vector expRev = expected;
        oven::reverse(expRev); // vector needed instead iterator_range.
        if (!tests_detail::bidirectional_r(tests_detail::make_reversed(rng), expRev)) {
            BOOST_ASSERT(false);
            return false;
        }
    }

    {
        if (!tests_detail::bidirectional_r(rng|const_referenced, expected)) {
            BOOST_ASSERT(false);
            return false;
        }

        Vector expRev = expected;
        oven::reverse(expRev);
        if (!tests_detail::bidirectional_r(tests_detail::make_reversed(rng|const_referenced), expRev)) {
            BOOST_ASSERT(false);
            return false;
        }
    }

    return true;
}


template< class Range, class Vector >
bool test_Bidirectional_Readable_Writable(Range& rng, Vector const& expected)
{
    BOOST_ASSERT(oven::distance(expected) >= 3);
    BOOST_ASSERT(oven::distance(rng) == oven::distance(expected));

    if (!oven::test_Bidirectional_Readable(rng, expected)) {
            BOOST_ASSERT(false);
            return false;
        }

    {
        if (!tests_detail::bidirectional_rw(rng, expected)) {
            BOOST_ASSERT(false);
            return false;
        }

        Vector expRev = expected;
        oven::reverse(expRev);
        if (!tests_detail::bidirectional_rw(tests_detail::make_reversed(rng), expRev)) {
            BOOST_ASSERT(false);
            return false;
        }
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

        if (!oven::test_Bidirectional_Readable(rng, expected)) {
            BOOST_ASSERT(false);
            return false;
        }

        boost::random_access_readable_iterator_test(
            boost::begin(rng), static_cast<int>(oven::distance(expected)), expected
        );

        return true;
    }


    template< class Range, class Vector >
    bool random_access_rw(Range& rng, Vector const& expected)
    {
        PSTADE_CONCEPT_ASSERT((Writable<Range>));

        if (!oven::test_Bidirectional_Readable_Writable(rng, expected)) {
            BOOST_ASSERT(false);
            return false;
        }

        Vector exp = expected;

        oven::sort(exp);
        oven::sort(rng);
        if (!oven::equals(rng, exp)) {
            BOOST_ASSERT(false);
            return false;
        }

        oven::random_shuffle(exp);
        oven::random_shuffle(rng);
        oven::stable_sort(exp);
        oven::stable_sort(rng);
        if (!oven::equals(rng, exp)) {
            BOOST_ASSERT(false);
            return false;
        }

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
        if (!tests_detail::random_access_r(rng, expected)) {
            BOOST_ASSERT(false);
            return false;
        }

        Vector expRev = expected;
        oven::reverse(expRev);
        if (!tests_detail::random_access_r(tests_detail::make_reversed(rng), expRev)) {
            BOOST_ASSERT(false);
            return false;
        }
    }

    {
        if (!tests_detail::random_access_r(rng|const_referenced, expected)) {
            BOOST_ASSERT(false);
            return false;
        }

        Vector expRev = expected;
        oven::reverse(expRev);
        if (!tests_detail::random_access_r(tests_detail::make_reversed(rng|const_referenced), expRev)) {
            BOOST_ASSERT(false);
            return false;
        }
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
        if (!tests_detail::random_access_rw(rng, expected)) {
            BOOST_ASSERT(false);
            return false;
        }

        Vector expRev = expected;
        oven::reverse(expRev);
        if (!tests_detail::random_access_rw(tests_detail::make_reversed(rng), expRev)) {
            BOOST_ASSERT(false);
            return false;
        }
    }

    return true;
}


// Misc
//

namespace tests_detail {


    template< class Range >
    bool is_empty(Range& rng)
    {
        if(!boost::empty(rng)) {
            BOOST_ASSERT(false);
            return false;
        }

        return true;
    }


} // namespace tests_detail


template< class Range >
bool test_empty(Range& rng)
{
    if(!tests_detail::is_empty(rng)) {
        BOOST_ASSERT(false);
        return false;
    }

    if(!tests_detail::is_empty(rng|const_referenced)) {
        BOOST_ASSERT(false);
        return false;
    }

    return true;
}


template< class To, class From >
bool test_Copyable(From const& from)
{
    // CopyConstructible needs the normal 'operator&',
    // but some class doesn't have it...
    // PSTADE_CONCEPT_ASSERT((boost::CopyConstructible<To>));

    To to = from|copied;

    if (!oven::equals(from, oven::copy_range<To>(from))) {
        BOOST_ASSERT(false);
        return false;
    }

    if (!oven::equals(from, to)) {
        BOOST_ASSERT(false);
        return false;
    }

    return true;
}


} } // namespace pstade::oven


#endif
