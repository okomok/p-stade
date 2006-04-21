#ifndef PSTADE_OVEN_ISTREAM_RANGE_HPP
#define PSTADE_OVEN_ISTREAM_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// basic_istream can maybe a range ?
//


#include <cstddef>  // ptrdiff_t
#include <iosfwd>   // basic_istream
#include <iterator> // istream_iterator
#include <string>   // char_traits
#include <boost/range/iterator_range.hpp>
#include <boost/type.hpp>
#include "./is_lightweight_proxy.hpp"


namespace pstade { namespace oven {


template<
    class T,
    class CharT = char,
    class TraitsT = std::char_traits<CharT>,
    class DistanceT = std::ptrdiff_t
>
struct istream_range :
    boost::iterator_range< std::istream_iterator<T, CharT, TraitsT, DistanceT> >
{
private:
    typedef std::istream_iterator<T, CharT, TraitsT, DistanceT> iter_t;
    typedef boost::iterator_range<iter_t> super_t;

public:
    explicit istream_range(std::basic_istream<CharT, TraitsT>& in) :
        super_t(iter_t(in), iter_t())
    { }
};


template< class T, class CharT, class TraitsT, class DistanceT > inline
const istream_range<T, CharT, TraitsT, DistanceT>
make_istream_range(boost::type<T>, std::basic_istream<CharT, TraitsT>& in, boost::type<DistanceT>)
{
    return istream_range<T, CharT, TraitsT, DistanceT>(in);
}


// default DistanceT
template< class T, class CharT, class TraitsT > inline
const istream_range<T, CharT, TraitsT>
make_istream_range(boost::type<T>, std::basic_istream<CharT, TraitsT>& in)
{
    return istream_range<T, CharT, TraitsT>(in);
}


// CharT == T
template< class CharT, class TraitsT, class DistanceT > inline
const istream_range<CharT, CharT, TraitsT, DistanceT>
make_istream_range(std::basic_istream<CharT, TraitsT>& in, boost::type<DistanceT>)
{
    return istream_range<CharT, CharT, TraitsT, DistanceT>(in);
}


// CharT == T, default DistanceT
template< class CharT, class TraitsT > inline
const istream_range<CharT, CharT, TraitsT>
make_istream_range(std::basic_istream<CharT, TraitsT>& in)
{
    return istream_range<CharT, CharT, TraitsT>(in);
}


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::istream_range, 4)


#endif
