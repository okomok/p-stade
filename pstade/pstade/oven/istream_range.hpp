#ifndef PSTADE_OVEN_ISTREAM_RANGE_HPP
#define PSTADE_OVEN_ISTREAM_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef>  // ptrdiff_t
#include <iosfwd>   // basic_istream
#include <iterator> // istream_iterator
#include <string>   // char_traits
#include <boost/range/iterator_range.hpp>
#include "./is_lightweight_proxy.hpp"


namespace pstade { namespace oven {


namespace istream_range_detail {


    template<
        class Value,
        class CharT,
        class Traits,
        class Difference
    >
    struct super_
    {
        typedef boost::iterator_range<
            std::istream_iterator<Value, CharT, Traits, Difference>
        > type;
    };


} // namespace istream_range_detail


template<
    class Value,
    class CharT = char,
    class Traits = std::char_traits<CharT>,
    class Difference = std::ptrdiff_t
>
struct istream_range :
    istream_range_detail::super_<Value, CharT, Traits, Difference>::type
{
private:
    typedef typename istream_range_detail::super_<Value, CharT, Traits, Difference>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit istream_range(std::basic_istream<CharT, Traits>& is) :
        super_t(iter_t(is), iter_t())
    { }
};


template< class Value, class CharT, class Traits > inline const
istream_range<Value, CharT, Traits>
make_istream_range(std::basic_istream<CharT, Traits>& is)
{
    return istream_range<Value, CharT, Traits>(is);
}


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::istream_range, 4)


#endif
