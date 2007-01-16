#ifndef PSTADE_OVEN_STREAM_INPUT_HPP
#define PSTADE_OVEN_STREAM_INPUT_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
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
#include "./iter_range.hpp"


namespace pstade { namespace oven {


// stream_input
//

template<
    class Value,
    class Difference = std::ptrdiff_t
>
struct op_stream_input :
    callable< op_stream_input<Value, Difference> >
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
    Result call(IStream& is) const
    {
        typedef typename Result::iterator iter_t;
        return Result(iter_t(is), iter_t());
    }
};

template< class Value, class IStream > inline
typename boost::result_of<op_stream_input<Value>(IStream&)>::type
stream_input(IStream& is)
{
    return op_stream_input<Value>()(is);
}


// streambuf_input
//

struct op_streambuf_input :
    callable<op_streambuf_input>
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
    Result call(std::basic_istream<CharT, Traits>& is) const
    {
        typedef typename Result::iterator iter_t;
        return Result(iter_t(is), iter_t());
    }

    template< class Result, class CharT, class Traits >
    Result call(std::basic_streambuf<CharT, Traits> *pb) const
    {
        typedef typename Result::iterator iter_t;
        return Result(iter_t(pb), iter_t());
    }
};

PSTADE_CONSTANT(streambuf_input, (op_streambuf_input))


} } // namespace pstade::oven


#endif
