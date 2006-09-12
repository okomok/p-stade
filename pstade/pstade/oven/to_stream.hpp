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
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./function_output_iterator.hpp"


namespace pstade { namespace oven {


template< class OStream >
struct stream_output_fun
{
    typedef OStream stream_type;
    typedef void result_type;

    explicit stream_output_fun(OStream& os) :
        m_pos(boost::addressof(os))
    { }

    template< class Value >
    void operator()(Value const& val) const
    {
        // Note:
        // 'Value' is the type of dereference of iterator,
        // which can be a type that is *convertible* to 'value_type'.
        // In such case, 'to_ostream' is preferable.
        *m_pos << val;
    }

    OStream& stream() const
    {
        return *m_pos;
    }

private:
    OStream *m_pos; // be a pointer for Assignable.
};


template< class OStream > inline
function_output_iterator< stream_output_fun<OStream> > const
to_stream(OStream& os)
{
    return oven::to_function(stream_output_fun<OStream>(os));
}


struct baby_stream_base
{
    template< class Unused, class FunOutIter >
    struct result
    {
        typedef typename FunOutIter::function_type::stream_type const type;
    };

    template< class Result, class FunOutIter >
    Result call(FunOutIter const& it)
    {
        return it.function().stream();
    }
};


PSTADE_EGG_FUNCTION(stream_base, baby_stream_base)
PSTADE_EGG_PIPABLE(to_stream_base, baby_stream_base)


template< class Value, class CharT, class Traits > inline
std::ostream_iterator<CharT, Traits> const
to_ostream(std::basic_ostream<CharT, Traits>& os)
{
    return std::ostream_iterator<Value, CharT, Traits>(os);
}

template< class Value, class CharT, class Traits > inline
std::ostream_iterator<CharT, Traits> const
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


} } // namespace pstade::oven


#endif
