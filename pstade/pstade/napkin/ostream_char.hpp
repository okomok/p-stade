#ifndef PSTADE_NAPKIN_OSTREAM_CHAR_HPP
#define PSTADE_NAPKIN_OSTREAM_CHAR_HPP


// PStade.Napkin
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace napkin {


template< class OStream >
struct ostream_char
{
    typedef typename OStream::char_type type;
};


} } // namespace pstade::napkin


#endif
