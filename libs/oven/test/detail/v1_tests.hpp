#ifndef PSTADE_LIBS_OVEN_TEST_DETAIL_V1_TESTS_HPP
#define PSTADE_LIBS_OVEN_TEST_DETAIL_V1_TESTS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// These tests assume:
//   1. Every Range is Readable; 'range_value' type is CopyConstructible.
//   2. 'range_reference' type of ForwardRange is a reference type.


#if !defined(PSTADE_CONCEPT_CHECK) \
    && !defined(PSTADE_OVEN_TESTS_NO_CONCEPT_CHECK)
#define PSTADE_CONCEPT_CHECK
#endif

// A range may be too long to diagnose.
// So some assertions cannot be in use code.
#if !defined(PSTADE_OVEN_TESTING) \
    && !defined(PSTADE_OVEN_NO_TESTING)
#define PSTADE_OVEN_TESTING
#endif

// It may make "memoized" range test be trivial to call 'distance'.
#if !defined(PSTADE_OVEN_TESTS_DONT_CALL_DISTANCE)
    #define PSTADE_OVEN_TESTS_DISTANCE_ASSERT BOOST_ASSERT
#else
    #define PSTADE_OVEN_TESTS_DISTANCE_ASSERT(X)
#endif


#include <pstade/oven/detail/prefix.hpp>
#include <algorithm>
#include <boost/assert.hpp>
#include <boost/concept_check.hpp>
#include <boost/foreach.hpp>
#include <boost/noncopyable.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/size.hpp>
#include <boost/next_prior.hpp>
#include <pstade/constant.hpp>
#include <pstade/egg/to_ref.hpp>
#include <pstade/unused.hpp>
#include <pstade/oven/concepts.hpp>
#include <pstade/oven/distance.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/iter_range.hpp>
#include <pstade/oven/range_difference.hpp>
#include <pstade/oven/range_iterator.hpp>
#include <pstade/oven/range_value.hpp>
#include "./new_iterator_tests.hpp"


// you need not include them.
#include <vector>
#include <pstade/concept.hpp>
#include <pstade/oven/copied.hpp>


#if !defined(PSTADE_OVEN_TESTS_REVERSE_RANGE_TESTING)
    #include <pstade/oven/reversed.hpp>
    #include <pstade/result_of.hpp>
#else
    #include <boost/iterator/reverse_iterator.hpp>
#endif


namespace pstade { namespace oven {


template< class Range, class Vector >
bool test_SinglePass_Readable(Range& rng, Vector const& expected)
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
    PSTADE_CONCEPT_ASSERT((Readable<Range>));

    typedef typename range_iterator<Range>::type iter_t;
    iter_t first = boost::begin(rng);
    iter_t last  = boost::end(rng);
    BOOST_ASSERT(first == first);
    BOOST_ASSERT(last == last);
    pstade::unused(first, last);

    if (!oven::equals(rng, expected)) { // In fact, Incrementable only.
        BOOST_ASSERT("test_SinglePass_Readable failed." && false);
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
            boost::begin(rng), std::remove(boost::begin(rng), boost::end(rng), v)
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
            boost::begin(rng1), std::search(boost::begin(rng1), boost::end(rng1), boost::begin(rng2), boost::end(rng2))
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

        boost::forward_readable_iterator_test(
            boost::begin(rng), boost::next(boost::begin(rng)),
            expected[0], expected[1]
        );

        if (!oven::test_SinglePass_Readable(rng, expected)) {
            BOOST_ASSERT(false);
            return false;
        }

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

        std::copy(boost::begin(expected), boost::end(expected), boost::begin(rng)); // restore
        return true;
    }


    template <class Iterator>
    void swappable_iter_test(Iterator i, Iterator j)
    {
        using std::iter_swap;

        Iterator i2(i), j2(j);
        typename boost::iterator_value<Iterator>::type bi = *i, bj = *j;
        iter_swap(i2, j2);
        typename boost::iterator_value<Iterator>::type ai = *i, aj = *j;
        BOOST_ASSERT("swappable_iter_test failed" && bi == aj);
        BOOST_ASSERT("swappable_iter_test failed" && bj == ai);
    }

    template< class Range, class Vector >
    bool forward_swappable(Range& rng, Vector const& expected)
    {
        tests_detail::swappable_iter_test(
            boost::begin(rng), boost::next(boost::begin(rng))
        );

        BOOST_ASSERT(expected[1] == *boost::begin(rng));
        BOOST_ASSERT(expected[0] == *boost::next(boost::begin(rng)));

        tests_detail::swappable_iter_test(
            boost::begin(rng), boost::next(boost::begin(rng))
        );

        BOOST_ASSERT(expected[0] == *boost::begin(rng));
        BOOST_ASSERT(expected[1] == *boost::next(boost::begin(rng)));
        return true;
    }


} // namespace tests_detail


template< class Range, class Vector >
bool test_Forward_Readable(Range& rng, Vector const& expected)
{
    PSTADE_OVEN_TESTS_DISTANCE_ASSERT(oven::distance(expected) >= 3);
    PSTADE_OVEN_TESTS_DISTANCE_ASSERT(oven::distance(rng) == oven::distance(expected));
#if defined(PSTADE_OVEN_BOOST_RANGE_VERSION_1)
    PSTADE_OVEN_TESTS_DISTANCE_ASSERT(boost::size(rng) == boost::size(expected));
#endif

    {
        if (!tests_detail::forward_r(rng, expected)) {
            BOOST_ASSERT(false);
            return false;
        }
    }

    {
        if (!tests_detail::forward_r(rng|egg::to_cref, expected)) {
            BOOST_ASSERT(false);
            return false;
        }
    }

    return true;
}


template< class Range, class Vector >
bool test_Forward_Readable_Writable(Range& rng, Vector const& expected)
{
    PSTADE_OVEN_TESTS_DISTANCE_ASSERT(oven::distance(expected) >= 3);
    PSTADE_OVEN_TESTS_DISTANCE_ASSERT(oven::distance(rng) == oven::distance(expected));

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

    {
        if (!tests_detail::forward_swappable(rng, expected)) {
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
    typename pstade::result_of<op_make_reversed(Range&)>::type
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

        boost::bidirectional_readable_iterator_test(
            boost::begin(rng),
            expected[0], expected[1]
        );

        if (!oven::test_Forward_Readable(rng, expected)) {
            BOOST_ASSERT(false);
            return false;
        }

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
        std::stable_partition(boost::begin(exp), boost::end(exp), tests_detail::make_less_than(tests_detail::make_pivot(expected)));
        std::stable_partition(boost::begin(rng), boost::end(rng), tests_detail::make_less_than(tests_detail::make_pivot(expected)));
        if (!oven::equals(rng, exp)) { // strictly speaking, can fail :-)
            BOOST_ASSERT(false);
            return false;
        }

        std::copy(boost::begin(expected), boost::end(expected), boost::begin(rng)); // restore
        return true;
    }


} // namespace tests_detail


template< class Range, class Vector >
bool test_Bidirectional_Readable(Range& rng, Vector const& expected)
{
    PSTADE_OVEN_TESTS_DISTANCE_ASSERT(oven::distance(expected) >= 3);
    PSTADE_OVEN_TESTS_DISTANCE_ASSERT(oven::distance(rng) == oven::distance(expected));

    {
        if (!tests_detail::bidirectional_r(rng, expected)) {
            BOOST_ASSERT(false);
            return false;
        }

        Vector expRev = expected;
        std::reverse(boost::begin(expRev), boost::end(expRev));// vector needed instead iterator_range.
        if (!tests_detail::bidirectional_r(tests_detail::make_reversed(rng), expRev)) {
            BOOST_ASSERT(false);
            return false;
        }
    }

    {
        if (!tests_detail::bidirectional_r(rng|egg::to_cref, expected)) {
            BOOST_ASSERT(false);
            return false;
        }

        Vector expRev = expected;
        std::reverse(boost::begin(expRev), boost::end(expRev));
        if (!tests_detail::bidirectional_r(tests_detail::make_reversed(rng|egg::to_cref), expRev)) {
            BOOST_ASSERT(false);
            return false;
        }
    }

    return true;
}


template< class Range, class Vector >
bool test_Bidirectional_Readable_Writable(Range& rng, Vector const& expected)
{
    PSTADE_OVEN_TESTS_DISTANCE_ASSERT(oven::distance(expected) >= 3);
    PSTADE_OVEN_TESTS_DISTANCE_ASSERT(oven::distance(rng) == oven::distance(expected));

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
        std::reverse(boost::begin(expRev), boost::end(expRev));
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

        std::sort(boost::begin(exp), boost::end(exp));
        std::sort(boost::begin(rng), boost::end(rng));
        if (!oven::equals(rng, exp)) {
            BOOST_ASSERT(false);
            return false;
        }

        std::random_shuffle(boost::begin(exp), boost::end(exp));
        std::random_shuffle(boost::begin(rng), boost::end(rng));
        std::stable_sort(boost::begin(exp), boost::end(exp));
        std::stable_sort(boost::begin(rng), boost::end(rng));
        if (!oven::equals(rng, exp)) {
            BOOST_ASSERT(false);
            return false;
        }

        std::copy(boost::begin(expected), boost::end(expected), boost::begin(rng)); // restore
        return true;
    }


} // namespace tests_detail


template< class Range, class Vector >
bool test_RandomAccess_Readable(Range& rng, Vector const& expected)
{
    PSTADE_OVEN_TESTS_DISTANCE_ASSERT(oven::distance(expected) >= 3);
    PSTADE_OVEN_TESTS_DISTANCE_ASSERT(oven::distance(rng) == oven::distance(expected));

    {
        if (!tests_detail::random_access_r(rng, expected)) {
            BOOST_ASSERT(false);
            return false;
        }

        Vector expRev = expected;
        std::reverse(boost::begin(expRev), boost::end(expRev));
        if (!tests_detail::random_access_r(tests_detail::make_reversed(rng), expRev)) {
            BOOST_ASSERT(false);
            return false;
        }
    }

    {
        if (!tests_detail::random_access_r(rng|egg::to_cref, expected)) {
            BOOST_ASSERT(false);
            return false;
        }

        Vector expRev = expected;
        std::reverse(boost::begin(expRev), boost::end(expRev));
        if (!tests_detail::random_access_r(tests_detail::make_reversed(rng|egg::to_cref), expRev)) {
            BOOST_ASSERT(false);
            return false;
        }
    }

    return true;
}


template< class Range, class Vector >
bool test_RandomAccess_Readable_Writable(Range& rng, Vector const& expected)
{
    PSTADE_OVEN_TESTS_DISTANCE_ASSERT(oven::distance(expected) >= 3);

#if BOOST_WORKAROUND(BOOST_MSVC, == 1310) && !defined(PSTADE_CONCEPT_CHECK) && !defined(NDEBUG)
    // Workaround:
    // Under VC++7.1 + No PSTADE_CONCEPT_CHECK + Debug mode,
    // 'oven::distance(rng)' sometimes fails to find ADL 'boost_range_end' of
    // const-qualified ranges without the following line. Weird!
    boost::const_end(rng);
    // Note that another workaround is to remove the const-qualifier
    // from the 'oven::distance' implementation.
#endif

    PSTADE_OVEN_TESTS_DISTANCE_ASSERT(oven::distance(rng) == oven::distance(expected));

    if (!oven::test_RandomAccess_Readable(rng, expected))
        return false;

    {
        if (!tests_detail::random_access_rw(rng, expected)) {
            BOOST_ASSERT(false);
            return false;
        }

        Vector expRev = expected;
        std::reverse(boost::begin(expRev), boost::end(expRev));
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

    if(!tests_detail::is_empty(rng|egg::to_cref)) {
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


namespace tests_detail {


    bool is_lightweight_proxy(boost::mpl::true_ *)
    {
        return true;
    }

    bool is_lightweight_proxy(boost::mpl::false_ *)
    {
        return false;
    }


} // namespace tests_detail


template< class Range > inline
bool test_is_lightweight_proxy(Range const& rng)
{
    return tests_detail::is_lightweight_proxy(BOOST_FOREACH_IS_LIGHTWEIGHT_PROXY(rng));
}


template< class Range >
struct test_noncopyable_range :
    iter_range_of<Range>::type,
    private boost::noncopyable
{
private:
    typedef typename iter_range_of<Range>::type super_t;

public:
    explicit test_noncopyable_range(Range& rng) :
        super_t(rng)
    { };
};


namespace tests_detail {


    struct a_noncopyable_range :
        std::vector<int>,
        private boost::noncopyable
    {
        a_noncopyable_range()
        {
            // Some adaptors dislike an empty range.
            push_back(1); push_back(2); push_back(3);
        }
    };


} // namespace tests_detail


PSTADE_CONSTANT(test_never_copy, (tests_detail::a_noncopyable_range))


} } // namespace pstade::oven


#endif
