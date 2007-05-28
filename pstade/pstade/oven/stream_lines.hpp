#ifndef PSTADE_OVEN_STREAM_LINES_HPP
#define PSTADE_OVEN_STREAM_LINES_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/prelude.hpp"
#include <memory> // allocator
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/use_default.hpp>
#include "./detail/istream_line_iterator.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


template<
    class Allocator = boost::use_default
>
struct op_stream_lines :
    callable< op_stream_lines<Allocator> >
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


PSTADE_CONSTANT(stream_lines, (op_stream_lines<>))


} } // namespace pstade::oven


#endif
