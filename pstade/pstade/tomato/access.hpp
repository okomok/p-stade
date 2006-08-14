#ifndef PSTADE_TOMATO_ACCESS_HPP
#define PSTADE_TOMATO_ACCESS_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp>
#include "./boolean_cast.hpp"


namespace pstade { namespace tomato {


class access
{
public:
    template< class T > static
    BOOL detail_on_idle(T& x)
    {
        return x.on_idle()|booleanized;
    }

    template< class T > static
    BOOL detail_pre_translate_message(T& x, MSG *pMsg)
    {
        return x.pre_translate_message(*pMsg)|booleanized;
    }

    template< class T > static
    TCHAR const *detail_c_str(T const& str)
    {
        return str.pstade_tomato_c_str();
    }
};


} } // namespace pstade::tomato


#endif
