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
#include <pstade/egg/baby_auto.hpp>
#include <pstade/egg/pipable.hpp>
#include "./function_output_iterator.hpp"


namespace pstade { namespace oven {


// 'Traits' should be deduced,
// so we define...
//

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


// Note:
// 'Value' is the type of dereference of iterator,
// which can be a type that is *convertible* to 'value_type'.
// In such case, 'to_ostream' above is preferable.
//

template< class OStream >
struct stream_output_fun
{

    typedef void result_type;

    explicit stream_output_fun(OStream& os) :
        m_pos(boost::addressof(os))
    { }

    template< class Value >
    void operator()(Value const& val) const
    {

        *m_pos << val;
    }

// as "adaptor", 'oven::to_base' can kick in!
    typedef OStream base_type;

    OStream& base() const
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


// See:
// 'oven::to_counter_base' as for the design rationale.
//

template< class OStream > inline
OStream&
stream_base(function_output_iterator< stream_output_fun<OStream> > const& it)
{
    return it.base().base();
}


struct stream_base_class
{
    template< class OStream, class FunOutIter >
    static OStream& call(FunOutIter const& it)
    {
        return oven::stream_base<OStream>(it);
    }
};

PSTADE_EGG_PIPABLE(to_stream_base, egg::baby_auto<stream_base_class>)


} } // namespace pstade::oven


#endif
