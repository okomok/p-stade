#ifndef PSTADE_OVEN_ISTREAMBUF_RANGE_HPP
#define PSTADE_OVEN_ISTREAMBUF_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iosfwd>   // basic_istream, basic_streambuf
#include <iterator> // istreambuf_iterator
#include <string>   // char_traits
#include <boost/range/iterator_range.hpp>
#include "./as_lightweight_proxy.hpp"


namespace pstade { namespace oven {


namespace istreambuf_range_detail {


    template< class CharT, class Traits >
    struct super_
    {
        typedef boost::iterator_range<
            std::istreambuf_iterator<CharT, Traits>
        > type;
    };


} // namespace istreambuf_range_detail


template<
    class CharT,
    class Traits = std::char_traits<CharT>
>
struct istreambuf_range :
    istreambuf_range_detail::super_<CharT, Traits>::type,
    private as_lightweight_proxy< istreambuf_range<CharT, Traits> >
{
private:
    typedef typename istreambuf_range_detail::super_<CharT, Traits>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit istreambuf_range(std::basic_istream<CharT, Traits>& is) :
        super_t(iter_t(is), iter_t())
    { }

    explicit istreambuf_range(std::basic_streambuf<CharT, Traits> *pb) :
        super_t(iter_t(pb), iter_t())
    { }
};


template< class CharT, class Traits > inline
istreambuf_range<CharT, Traits> const
make_istreambuf_range(std::basic_istream<CharT, Traits>& is)
{
    return istreambuf_range<CharT, Traits>(is);
}


template< class CharT, class Traits > inline
istreambuf_range<CharT, Traits> const
make_istreambuf_range(std::basic_streambuf<CharT, Traits> *pb)
{
    return istreambuf_range<CharT, Traits>(pb);
}


} } // namespace pstade::oven


#endif
