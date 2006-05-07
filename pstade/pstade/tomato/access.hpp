#ifndef PSTADE_TOMATO_ACCESS_HPP
#define PSTADE_TOMATO_ACCESS_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/sdk/windows.hpp>
#include "./boolean_cast.hpp"


namespace pstade { namespace tomato {


class access
{
public:
    template< class T > static
    bool detail_pre_translate_message(T& x, MSG* pMsg)
    {
        return tomato::boolean(x.pre_translate_message(pMsg));
    }

    template< class T > static
    bool detail_on_idle(T& x)
    {
        return tomato::boolean(x.on_idle());
    }
};


} } // namespace pstade::tomato


#endif
