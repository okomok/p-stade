#ifndef PSTADE_OVEN_TO_STREAM_HPP
#define PSTADE_OVEN_TO_STREAM_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iosfwd> // basic_ostream/streambuf
#include <iterator>
#include <boost/utility/addressof.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/function.hpp>
#include "./function_output_iterator.hpp"


namespace pstade { namespace oven {


// 'Traits' should be deduced,
// so we define...
//

template< class Value, class CharT, class Traits > inline
std::ostream_iterator<Value, CharT, Traits> const
to_ostream(std::basic_ostream<CharT, Traits>& os)
{
    return std::ostream_iterator<Value, CharT, Traits>(os);
}

template< class Value, class CharT, class Traits > inline
std::ostream_iterator<Value, CharT, Traits> const
to_ostream(std::basic_ostream<CharT, Traits>& os, CharT const *delim)
{
    return std::ostream_iterator<Value, CharT, Traits>(os, delim);
}


template< class CharT, class Traits > inline
std::ostreambuf_iterator<CharT, Traits> const
to_ostreambuf(std::basic_ostream<CharT, Traits>& os)
{
    return std::ostreambuf_iterator<CharT, Traits>(os);
}


template< class CharT, class Traits > inline
std::ostreambuf_iterator<CharT, Traits> const
to_ostreambuf(std::basic_streambuf<CharT, Traits> *pb)
{
    return std::ostreambuf_iterator<CharT, Traits>(pb);
}


// Note:
// 'Value' is the type of dereference of iterator,
// which can be a type that is *convertible* to 'value_type'.
// In such case, 'to_ostream' above is preferable.
//

template< class Stream >
struct op_stream_output
{
    typedef Stream stream_type;
    typedef void result_type;

    // Note:
    // DefaultConstructible is not required
    // as OutputIterator is not.

    explicit op_stream_output(Stream& s) :
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

// as "adaptor", 'oven::adapted_to' kicks in!
    Stream& base() const
    {
        return *m_ps;
    }

private:
    Stream *m_ps; // be a pointer for Assignable.
};


template< class Stream >
struct baby_to_stream
{
    typedef typename
        boost::result_of<op_to_function(op_stream_output<Stream>)>::type
    result;

    result call(Stream& s)
    {
        return result(typename result::function_type(s));
    }
};

PSTADE_FUNCTION(to_stream, (baby_to_stream<_>))


} } // namespace pstade::oven


#endif
