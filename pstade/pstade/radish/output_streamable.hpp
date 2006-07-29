#ifndef PSTADE_RADISH_OUTPUT_STREAMABLE_HPP
#define PSTADE_RADISH_OUTPUT_STREAMABLE_HPP


// PStade.Radish
//
// Copyright MB 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iosfwd> // basic_ostream
#include <boost/detail/templated_streams.hpp>
#include <pstade/adl_barrier.hpp>
#include "./access.hpp"


namespace pstade { namespace radish {

PSTADE_ADL_BARRIER(output_streamable) {


template< class T >
struct output_streamable
{
    template< BOOST_TEMPLATED_STREAM_ARGS(CharT, Traits) >
    friend
    BOOST_TEMPLATED_STREAM(ostream, CharT, Traits)&
    operator<<(
        BOOST_TEMPLATED_STREAM(ostream, CharT, Traits)& os,
        T const& x)
    {
        access::detail_output(x, os);
        return os;
    }
};


} // ADL barrier

} } // namespace pstade::radish


#endif
