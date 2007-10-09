#ifndef PSTADE_OVEN_ITER_RANGE_HPP
#define PSTADE_OVEN_ITER_RANGE_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// The minimal "iterator_range".
// This range has...
//   no deep equality-comparison.
//   neither 'front' nor 'back'.
//   no implicit template-constructor.


#include <cstddef> // size_t
#include <utility> // pair
#include <boost/iterator/iterator_traits.hpp>
#include <boost/operators.hpp> // equality_comparable
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <pstade/disable_if_copy.hpp>
#include <pstade/egg/do_swap.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/radish/bool_testable.hpp>
#include <pstade/radish/swappable.hpp>
#include <pstade/reset_assignment.hpp>
#include "./concepts.hpp"
#include "./detail/config.hpp"
#include "./detail/iter_distance.hpp"
#include "./lightweight_copyable.hpp"
#include "./range_iterator.hpp"

#if defined(PSTADE_OVEN_BOOST_RANGE_VERSION_1)
    #include <pstade/egg/copy.hpp>
#endif


namespace pstade { namespace oven {


namespace iter_range_detail {


    // See <pstade/radish/null_injector.hpp>.
    struct null_injector { };


} // namespace iter_range_detail


template<
    class Iterator,
    class Injector = iter_range_detail::null_injector
>
struct iter_range :
    boost::equality_comparable1< iter_range<Iterator, Injector>,
    radish::bool_testable      < iter_range<Iterator, Injector>,
    radish::swappable          < iter_range<Iterator, Injector>,
    lightweight_copyable       < iter_range<Iterator, Injector>,
    Injector > > > >
{
private:
    typedef iter_range self_t;

public:
// structors
    iter_range()
    { }

    template< class It, class In >
    iter_range(iter_range<It, In> const& other,
        typename enable_if< is_convertible<It, Iterator> >::type = 0
    ) :
        m_first(boost::begin(other)), m_last(boost::end(other))
    { }

    template< class Iterator_ >
    iter_range(Iterator_ first, Iterator_ last) :
        m_first(first), m_last(last)
    { }

    template< class Range >
    explicit iter_range(Range& rng, typename disable_if_copy<self_t, Range>::type = 0) :
        m_first(boost::begin(rng)), m_last(boost::end(rng))
    { }

    template< class Range >
    explicit iter_range(Range const& rng) :
        m_first(boost::begin(rng)), m_last(boost::end(rng))
    { }

// for "third-party" libraries
    template< class I >
    iter_range(std::pair<I, I> const& rng,
        typename enable_if< is_convertible<I, Iterator> >::type = 0
    ) :
        m_first(boost::begin(rng)), m_last(boost::end(rng))
    { }

    template< class I >
    iter_range(boost::iterator_range<I> const& rng,
        typename enable_if< is_convertible<I, Iterator> >::type = 0
    ) :
        m_first(boost::begin(rng)), m_last(boost::end(rng))
    { }

// assignments
    template< class Range >
    void reset(Range& rng)
    {
        m_first = boost::begin(rng);
        m_last  = boost::end(rng);
    }

    template< class Range >
    void reset(Range const& rng)
    {
        m_first = boost::begin(rng);
        m_last  = boost::end(rng);
    }

    PSTADE_RESET_ASSIGNMENT(iter_range)

    template< class Iterator_ >
    void reset(Iterator_ first, Iterator_ last)
    {
        m_first = first;
        m_last  = last;
    }

// range implementation
    typedef Iterator iterator;
    typedef Iterator const_iterator;
    typedef std::size_t size_type;

    Iterator begin() const
    {
        return m_first;
    }

    Iterator end() const
    {
        return m_last;
    }

#if defined(PSTADE_OVEN_BOOST_RANGE_VERSION_1)
    size_type size() const
    {
        return egg::copy<size_type>(detail::iter_distance(m_first, m_last));
    }
#endif

// convenience
    typedef self_t type;
    typedef typename boost::iterator_value<Iterator>::type      value_type;
    typedef typename boost::iterator_difference<Iterator>::type difference_type;
    typedef typename boost::iterator_reference<Iterator>::type  reference;

    // It seems useless to return bracket proxy when you need 'rng[i][j]' syntax.
    reference operator[](difference_type n) const
    {
        PSTADE_CONCEPT_ASSERT((RandomAccess<self_t>));
        BOOST_ASSERT(0 <= n);
        BOOST_ASSERT(n < m_last - m_first);
        return m_first[n];
    }

// equality_comparable
    bool operator==(self_t const& other) const
    {
        return m_first == other.m_first && m_last == other.m_last;
    }

// bool_testable
    operator radish::safe_bool() const
    {
        return radish::make_safe_bool(m_first != m_last);
    }

// swappable
    void swap(self_t& other)
    {
        egg::do_swap(m_first, other.m_first);
        egg::do_swap(m_last,  other.m_last);
    }

private:
    Iterator m_first, m_last;
};


template<
    class Range,
    class Injector = iter_range_detail::null_injector
>
struct iter_range_of
{
    typedef typename
        range_iterator<Range>::type
    iter_t;

    typedef
        iter_range<iter_t, Injector>
    type;
};


namespace make_iter_range_detail {


    struct baby
    {
        template< class Myself, class Iterator, class Iterator_ = void >
        struct apply
        {
            typedef typename
                pass_by_value<Iterator>::type
            iter_t;

            typedef
                iter_range<iter_t> const
            type;
        };

        // Two iterators may have different cv-qualifier.
        template< class Result, class Iterator, class Iterator_ >
        Result call(Iterator& first, Iterator_& last) const
        {
            return Result(first, last);
        }

        template< class Myself, class Range >
        struct apply<Myself, Range>
        {
            typedef typename
                iter_range_of<Range>::type const
            type;
        };

        template< class Result, class Range >
        Result call(Range& rng) const
        {
            // Prefer two arguments constructor for 'initial_values'.
            return Result(boost::begin(rng), boost::end(rng));
        }
    };


} // namespace make_iter_range_detail


typedef egg::function<make_iter_range_detail::baby> T_make_iter_range;
PSTADE_POD_CONSTANT((T_make_iter_range), make_iter_range) = {{}};


} } // namespace pstade::oven


#endif
