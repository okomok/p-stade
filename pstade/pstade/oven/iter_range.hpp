#ifndef PSTADE_OVEN_ITER_RANGE_HPP
#define PSTADE_OVEN_ITER_RANGE_HPP


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
//   neither 'front', 'back' nor 'operator[]'.
//   no implicit template-constructor.
//   strong guarantee assignment.


#include <algorithm> // swap
#include <cstddef> // size_t
#include <utility> // pair
#include <boost/iterator/iterator_traits.hpp>
#include <boost/operators.hpp> // equality_comparable
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/disable_if_copy.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/radish/bool_testable.hpp>
#include <pstade/radish/swappable.hpp>
#include "./lightweight_copyable.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace iter_range_detail {

    // VC7.1 complains if class hierarchy has two or more
    // private base. 'iter_range' is often used as base,
    // so it is better to use unique type just in case.
    struct empty_base { };

} // namespace iter_range_detail


template< class Iterator >
struct iter_range :
    private
        boost::equality_comparable< iter_range<Iterator>,
        radish::bool_testable     < iter_range<Iterator>,
        radish::swappable         < iter_range<Iterator>,
        lightweight_copyable      < iter_range<Iterator>,
        iter_range_detail::empty_base > > > >
{
private:
    typedef iter_range self_t;

public:
// structors
    iter_range()
    { }

    template< class I >
    iter_range(iter_range<I> const& other,
        typename enable_if< boost::is_convertible<I, Iterator> >::type = 0
    ) :
        m_first(boost::begin(other)), m_last(boost::end(other))
    { }

    template< class Iterator_ >
    iter_range(Iterator_ const& first, Iterator_ const& last) :
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

// assignments
    template< class Range >
    typename disable_if_copy_assign<self_t, Range>::type operator=(Range& rng)
    {
        // While no copy/assign of iterator throws (23.1/11),
        // 'begin/end' can throw (http://tinyurl.com/2ov9mw).
        self_t(rng).swap(*this);
        return *this;
    }

    template< class Range >
    self_t& operator=(Range const& rng)
    {
        self_t(rng).swap(*this);
        return *this;
    }

// for "third-party" libraries
    template< class I >
    iter_range(std::pair<I, I> const& rng,
        typename enable_if< boost::is_convertible<I, Iterator> >::type = 0
    ) :
        m_first(boost::begin(rng)), m_last(boost::end(rng))
    { }

    template< class I >
    iter_range(boost::iterator_range<I> const& rng,
        typename enable_if< boost::is_convertible<I, Iterator> >::type = 0
    ) :
        m_first(boost::begin(rng)), m_last(boost::end(rng))
    { }

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

// convenience
    typedef self_t type;
    typedef typename boost::iterator_value<Iterator>::type value_type;
    typedef typename boost::iterator_difference<Iterator>::type difference_type;
    typedef typename boost::iterator_reference<Iterator>::type reference;

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
        std::swap(m_first, other.m_first);
        std::swap(m_last,  other.m_last);
    }

private:
    Iterator m_first, m_last;
};


template< class Range >
struct iter_range_of
{
    typedef typename
        range_iterator<Range>::type
    iter_t;

    typedef
        iter_range<iter_t>
    type;
};


struct op_make_iter_range :
    callable<op_make_iter_range>
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
        return Result(rng);
    }
};


PSTADE_CONSTANT(make_iter_range, (op_make_iter_range))


} } // namespace pstade::oven


#endif
