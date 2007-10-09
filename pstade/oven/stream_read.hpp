#ifndef PSTADE_OVEN_STREAM_READ_HPP
#define PSTADE_OVEN_STREAM_READ_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef>  // ptrdiff_t
#include <iosfwd>   // basic_istream, basic_streambuf
#include <iterator> // istream_iterator
#include <boost/type_traits/remove_pointer.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/specified.hpp>
#include <pstade/pod_constant.hpp>
#include "./detail/istreambuf_iterator.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


// stream_read
//

template<
    class Value,
    class Difference = std::ptrdiff_t
>
struct tp_stream_read 
{
    struct baby
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

    typedef egg::function<baby> type;
};

template<
    class Value,
    class Difference = std::ptrdiff_t
>
struct X_stream_read :
    tp_stream_read<Value, Difference>::type
{ };

PSTADE_EGG_SPECIFIED1(stream_read, X_stream_read, (class))


// streambuf_read
//

namespace streambuf_read_detail {

    struct baby
    {
        template< class Myself, class IStream >
        struct apply
        {
            typedef typename
                boost::remove_pointer<IStream>::type
            stream_t;
          
            typedef
                detail::istreambuf_iterator<
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

} // namespace streambuf_read_detail

typedef egg::function<streambuf_read_detail::baby> T_streambuf_read;
PSTADE_POD_CONSTANT((T_streambuf_read), streambuf_read) = {{}};


} } // namespace pstade::oven


#endif
