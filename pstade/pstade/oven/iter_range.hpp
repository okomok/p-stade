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
//
// Note that it is impossible to implement 'back' and 'operator[]' safely,
// which was overlooked by 'boost::iterator_range'.
// Also, the copy-constructor of 'boost::iterator_range' is sub-optimal.


#include <algorithm> // swap
#include <cstddef> // size_t
#include <iosfwd> // basic_ostream
#include <boost/iterator/iterator_categories.hpp> // iterator_traversal
#include <boost/iterator/iterator_traits.hpp>
#include <boost/operators.hpp> // equality_comparable
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/radish/bool_testable.hpp>
#include <pstade/radish/swappable.hpp>
#include <pstade/unused_to_copy.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./range_iterator.hpp"
#include "./to_stream.hpp"


namespace pstade { namespace oven {


template< class Iterator >
struct iter_range;


namespace iter_range_detail {


    template< class Iterator >
    struct super_
    {
        typedef
            boost::equality_comparable< iter_range<Iterator>,
            radish::bool_testable     < iter_range<Iterator>,
            radish::swappable         < iter_range<Iterator>
            > > >
        type;
    };


} // namespace iter_range_detail


template< class Iterator >
struct iter_range :
    iter_range_detail::super_<Iterator>::type,
    private as_lightweight_proxy< iter_range<Iterator> >
{
private:
    typedef typename iter_range_detail::super_<Iterator>::type super_t;

public:
    typedef iter_range type;

// structors
    explicit iter_range()
    { }

    template< class Iterator_ >
    explicit iter_range(Iterator_ const& first, Iterator_ const& last) :
        m_first(first), m_last(last)
    { }

    template< class Range_ >
    explicit iter_range(Range_& rng, typename unused_to_copy<type, Range_>::type = 0) :
        m_first(boost::begin(rng)), m_last(boost::end(rng))
    { }

    template< class Range_ >
    explicit iter_range(Range_ const& rng) :
        m_first(boost::begin(rng)), m_last(boost::end(rng))
    { }

// copy-assignments
    template< class Range_ >
    typename unused_to_copy_assign<type, Range_>::type operator=(Range_& rng)
    {
        type(rng).swap(*this);
        return *this;
    }

    template< class Range_ >
    type& operator=(Range_ const& rng)
    {
        type(rng).swap(*this);
        return *this;
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

// convenience
    typedef typename boost::iterator_category<Iterator>::type   iterator_category;
    typedef typename boost::iterator_value<Iterator>::type      value_type;
    typedef typename boost::iterator_difference<Iterator>::type difference_type;
    typedef typename boost::iterator_pointer<Iterator>::type    pointer;
    typedef typename boost::iterator_reference<Iterator>::type  reference;
    typedef typename boost::iterator_traversal<Iterator>::type  iterator_traversal;

// bool_testable
    operator radish::safe_bool() const
    {
        return radish::make_safe_bool(m_first != m_last);
    }

// equality_comparable
    bool operator==(type const& other) const
    {
        return m_first == other.m_first && m_last == other.m_last;
    }

// swappable
    void swap(type& other)
    {
        std::swap(m_first, other.m_first);
        std::swap(m_last, other.m_last);
    }

private:
    Iterator m_first, m_last;
};


struct op_make_iter_range :
    callable<op_make_iter_range>
{
    template< class Myself, class Iterator, class Iterator_ = void >
    struct apply
    {
        typedef iter_range<typename boost::remove_cv<Iterator>::type> const type;
    };

    template< class Result, class Iterator, class Iterator_ >
    Result call(Iterator& first, Iterator_& last) const // two Iterators may have different cv-qualifier.
    {
        return Result(first, last);
    }

    template< class Myself, class Range >
    struct apply<Myself, Range>
    {
        typedef iter_range<typename range_iterator<Range>::type> const type;
    };

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return Result(rng);
    }
};

PSTADE_CONSTANT(make_iter_range, (op_make_iter_range))


template< class Iterator, class CharT, class Traits >
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, iter_range<Iterator> const& rng)
{
    os << '{';

    bool is_first = true;
    Iterator const last(boost::end(rng));

    for (Iterator first(boost::begin(rng)); first!= last; ++first) {
        if (!is_first)
            os << ',';
        else
            is_first = false;

        os << *first;
    }

    os << '}';
    return os;
}


} } // namespace pstade::oven


#endif
