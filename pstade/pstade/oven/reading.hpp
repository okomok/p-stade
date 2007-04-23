#ifndef PSTADE_OVEN_READING_HPP
#define PSTADE_OVEN_READING_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef>  // ptrdiff_t
#include <iosfwd>   // basic_istream, basic_streambuf
#include <iterator> // istream_iterator, istreambuf_iterator
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/specified.hpp>
#include <pstade/use_default.hpp>
#include "./detail/istream_line_iterator.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


// reading
//

template<
    class Value,
    class Difference = std::ptrdiff_t
>
struct op_reading :
    callable< op_reading<Value, Difference> >
{
    template< class Myself, class IStream >
    struct apply
    {
        typedef
            std::istream_iterator<
                Value,
                typename IStream::char_type,
                typename IStream::traits_type,
                Difference
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class IStream >
    Result call(IStream& s) const
    {
        typedef typename Result::iterator iter_t;
        return Result(iter_t(s), iter_t());
    }
};

PSTADE_SPECIFIED1(reading, op_reading, 1)


// reading_buf
//

struct op_reading_buf :
    callable<op_reading_buf>
{
    template< class Myself, class IStream >
    struct apply
    {
        typedef typename
            boost::remove_pointer<IStream>::type
        stream_t;
      
        typedef
            std::istreambuf_iterator<
                typename stream_t::char_type,
                typename stream_t::traits_type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class CharT, class Traits >
    Result call(std::basic_istream<CharT, Traits>& s) const
    {
        typedef typename Result::iterator iter_t;
        return Result(iter_t(s), iter_t());
    }

    template< class Result, class CharT, class Traits >
    Result call(std::basic_streambuf<CharT, Traits> *p) const
    {
        typedef typename Result::iterator iter_t;
        return Result(iter_t(p), iter_t());
    }
};

PSTADE_CONSTANT(reading_buf, (op_reading_buf))


// line_reading
//

template<
    class Allocator = boost::use_default
>
struct op_line_reading :
    callable< op_line_reading<Allocator> >
{
    template< class Myself, class IStream >
    struct apply
    {
        typedef typename
            IStream::char_type
        char_t;

        typedef
            hamigaki::istream_line_iterator<
                char_t,
                typename IStream::traits_type,
                typename use_default_to< Allocator, std::allocator<char_t> >::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class IStream >
    Result call(IStream& s) const
    {
        typedef typename Result::iterator iter_t;
        return Result(iter_t(s), iter_t());
    }
};

PSTADE_CONSTANT(line_reading, (op_line_reading<>))


} } // namespace pstade::oven


#endif
