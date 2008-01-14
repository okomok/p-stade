#ifndef PSTADE_OVEN_STREAM_LINES_HPP
#define PSTADE_OVEN_STREAM_LINES_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <memory> // allocator
#include <pstade/egg/function.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/use_default.hpp>
#include "./detail/istream_line_iterator.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace stream_lines_detail {


    template< class Allocator >
    struct little
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
                    typename if_use_default< Allocator, std::allocator<char_t> >::type
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


} // namespace stream_lines_detail


template< class Allocator = boost::use_default >
struct X_stream_lines :
    egg::function< stream_lines_detail::little<Allocator> >
{ };


typedef X_stream_lines<>::function_type T_stream_lines;
PSTADE_POD_CONSTANT((T_stream_lines), stream_lines) = {{}};


} } // namespace pstade::oven


#endif
