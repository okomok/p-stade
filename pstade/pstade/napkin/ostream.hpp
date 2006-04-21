#ifndef PSTADE_NAPKIN_OSTREAM_HPP
#define PSTADE_NAPKIN_OSTREAM_HPP


// PStade.Napkin
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/shared_ptr.hpp>
#include "./detail/basic_holder.hpp"
#include "./detail/basic_placeholder.hpp"
#include "./nout.hpp"


namespace pstade { namespace napkin {


template< class CharT >
struct basic_ostream
{
    explicit basic_ostream()
    {
        reset(nout);
    }

    template< class StringOutputable >
    explicit basic_ostream(StringOutputable& out) :
        m_pout(new detail::basic_holder<CharT, StringOutputable>(out))
    { };

    template< class OutputStreamable >
    basic_ostream& operator<<(const OutputStreamable& x)
    {
        m_pout->output(x);
        return *this;
    }

    template< class StringOutputable >
    void reset(StringOutputable& out)
    {
        m_pout.reset(new detail::basic_holder<CharT, StringOutputable>(out));
    }

private:
    boost::shared_ptr< detail::basic_placeholder<CharT> > m_pout;
};


typedef basic_ostream<char>
ostream;


typedef basic_ostream<wchar_t>
wostream;


} } // namespace pstade::napkin


#endif
