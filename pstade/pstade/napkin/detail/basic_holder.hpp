#ifndef PSTADE_NAPKIN_DETAIL_BASIC_HOLDER_HPP
#define PSTADE_NAPKIN_DETAIL_BASIC_HOLDER_HPP


// PStade.Napkin
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: <boost/any.hpp>
//
// Copyright Kevlin Henney, 2000, 2001, 2002. All rights reserved.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/noncopyable.hpp>
#include "../extension.hpp"
#include "./basic_placeholder.hpp"


namespace pstade { namespace napkin { namespace detail {


template< class T, class String > inline
void pstade_napkin_output(T& out, String psz)
{
    pstade_napkin_(pstade_napkin_extension::output(), out, psz);
}


template< class CharT, class StringOutputable >
struct basic_holder :
    basic_placeholder<CharT>,
    private boost::noncopyable
{
    explicit basic_holder(StringOutputable& out) :
        m_held(out)
    { }

protected:
    void override_output(const CharT *psz)
    {
        pstade_napkin_output(m_held, psz);
    }

private:
    StringOutputable& m_held;
};


} } } // namespace pstade::napkin::detail


#endif
