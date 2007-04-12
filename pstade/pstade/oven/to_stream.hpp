#ifndef PSTADE_OVEN_TO_STREAM_HPP
#define PSTADE_OVEN_TO_STREAM_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iosfwd> // basic_ostream/streambuf
#include <iterator>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/function.hpp>
#include <pstade/specified.hpp>
#include "./to_function.hpp"


namespace pstade { namespace oven {


// 'Traits' should be deduced,
// so we define...


// to_ostream
//

template< class Value >
struct op_to_ostream :
    callable< op_to_ostream<Value> >
{
    template< class Myself, class OStream, class Delim = void >
    struct apply
    {
        typedef
            std::ostream_iterator<
                Value,
                typename OStream::char_type,
                typename OStream::traits_type
            > const
        type;
    };

    template< class Result, class OStream >
    Result call(OStream& os) const
    {
        return Result(os);
    }

    template< class Result, class OStream, class CharT >
    Result call(OStream& os, CharT const *delim) const
    {
        return Result(os, delim);
    }
};

#define  PSTADE_SPECIFIED_PARAMS ((1)(2), to_ostream, op_to_ostream, 1)
#include PSTADE_SPECIFIED()


// to_ostreambuf
//

struct op_to_ostreambuf :
    callable<op_to_ostreambuf>
{
    template< class Myself, class OStream >
    struct apply
    {
        typedef typename
            boost::remove_pointer<OStream>::type
        stream_t;

        typedef
            std::ostreambuf_iterator<
                typename stream_t::char_type,
                typename stream_t::traits_type
            > const
        type;
    };

    template< class Result, class CharT, class Traits >
    Result call(std::basic_ostream<CharT, Traits>& os) const
    {
        return Result(os);
    }

    template< class Result, class CharT, class Traits >
    Result call(std::basic_streambuf<CharT, Traits> *pb) const
    {
        return Result(pb);
    }
};

PSTADE_CONSTANT(to_ostreambuf, (op_to_ostreambuf))


// to_stream
//

namespace to_stream_detail {

    // 'Value' is the type of dereference of iterator,
    // which can be a type that is *convertible* to 'value_type'.
    // In such case, 'to_ostream' above is preferable.

    template< class Stream >
    struct op_output
    {
        typedef Stream stream_type;
        typedef void result_type;

        // DefaultConstructible is not required
        // as OutputIterator is not.

        explicit op_output(Stream& s) :
            m_ps(boost::addressof(s))
        { }

        template< class Value >
        void operator()(Value const& val) const
        {
            *m_ps << val;
        }

        Stream& stream() const
        {
            return *m_ps;
        }

        // as "adaptor"; 'oven::adapted_to' kicks in!
        Stream& base() const
        {
            return *m_ps;
        }

    private:
        Stream *m_ps; // be a pointer for Assignable.
    };

    template< class Stream >
    struct baby
    {
        typedef typename
            boost::result_of<
                op_to_function(op_output<Stream>)
            >::type
        result_type;

        result_type operator()(Stream& s) const
        {
            return to_function(op_output<Stream>(s));
        }
    };

} // namespace to_stream_detail

PSTADE_FUNCTION(to_stream, (to_stream_detail::baby<_>))


} } // namespace pstade::oven


#endif
