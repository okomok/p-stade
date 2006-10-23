#ifndef PSTADE_OVEN_ITER_RANGE_HPP
#define PSTADE_OVEN_ITER_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// The minimal "iterator_range".
// This range has...
//   no deep equality-compare.
//   neither 'front', 'back' nor 'operator[]'.
//   the conversion using 'adaptor_to'.
//
// Note that it is impossible to implement 'back' and 'operator[]' safely,
// which was overlooked by 'boost::iterator_range'.
// Also, the copy-constructor of 'boost::iterator_range' is sub-optimal.


#include <algorithm> // swap
#include <cstddef> // size_t
#include <iosfwd> // basic_ostream
#include <boost/iterator/iterator_traits.hpp> // iterator_value
#include <boost/operators.hpp> // equality_comparable
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/radish/bool_testable.hpp>
#include <pstade/radish/swappable.hpp>
#include <pstade/unused_to_copy.hpp>
#include "./adaptor_to_base.hpp"
#include "./algorithm.hpp" // copy
#include "./range_iterator.hpp"
#include "./to_stream.hpp"


namespace pstade { namespace oven {


template< class Iterator >
struct iter_range;


namespace iter_range_detail {


    template< class Iterator >
    struct operators
    {
        typedef
            boost::equality_comparable< iter_range<Iterator>,
            radish::bool_testable     < iter_range<Iterator>,
            radish::swappable         < iter_range<Iterator>
            > > >
        type;
    };


    template< class Iterator >
    struct super_ :
        operators<Iterator>::type
    {
        typedef super_<Iterator> type;

    protected:
        super_()
        { }

        template< class Iterator_ >
        super_(Iterator_ const& first, Iterator_ const& last) :
            m_first(oven::adaptor_to<Iterator>(first)),
            m_last (oven::adaptor_to<Iterator>(last ))
        { }

        Iterator m_first, m_last;
    };


} // namespace iter_range_detail


template< class Iterator >
struct iter_range :
    iter_range_detail::super_<Iterator>::type
    
{
private:
    typedef typename iter_range_detail::super_<Iterator>::type super_t;

public:
    typedef iter_range type;

// structors
    iter_range()
    { }

    template< class Iterator_ >
    iter_range(Iterator_ const& first, Iterator_ const& last) :
        super_t(first, last)
    { }

    template< class Range_ >
    iter_range(Range_& rng,
        typename unused_to_copy<type, Range_>::type = 0
    ) :
        super_t(boost::begin(rng), boost::end(rng))
    { }

    template< class Range_ >
    iter_range(Range_ const& rng,
        typename unused_to_copy<type, Range_>::type = 0
    ) :
        super_t(boost::begin(rng), boost::end(rng))
    { }

// copy-assignments
    template< class Range_ >
    typename unused_to_copy_assign<type, Range_>::type
    operator=(Range_& rng)
    {
        type(rng).swap(*this);
        return *this;
    }

    template< class Range_ >
    typename unused_to_copy_assign<type, Range_>::type
    operator=(Range_ const& rng)
    {
        type(rng).swap(*this);
        return *this;
    }

// range implementations
    typedef Iterator iterator;
    typedef Iterator const_iterator;
    typedef std::size_t size_type;

    Iterator begin() const
    {
        return this->m_first;
    }

    Iterator end() const
    {
        return this->m_last;
    }

// bool_testable
    operator radish::safe_bool() const
    {
        return radish::make_safe_bool(this->m_first != this->m_last);
    }

// equality_comparable
    bool operator==(type const& other) const
    {
        return this->m_first == other.m_first && this->m_last == other.m_last;
    }

// swappable
    void swap(type& other)
    {
        std::swap(this->m_first, other.m_first);
        std::swap(this->m_last, other.m_last);
    }
};


template< class Iterator > inline
iter_range<Iterator> const
make_iter_range(Iterator const& first, Iterator const& last)
{
    return iter_range<Iterator>(first, last);
}

template< class Range > inline
iter_range<typename range_iterator<Range>::type> const
make_iter_range(Range& rng)
{
    return iter_range<typename range_iterator<Range>::type>(rng);
}

template< class Range > inline
iter_range<typename range_iterator_const<Range>::type> const
make_iter_range(Range const& rng)
{
    return iter_range<typename range_iterator_const<Range>::type>(rng);
}


template< class Iterator, class CharT, class Traits > inline
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, iter_range<Iterator> const& ir)
{
    oven::copy(ir, oven::to_ostream<typename boost::iterator_value<Iterator>::type>(os));
    return os;
}


} } // namespace pstade::oven


#endif
