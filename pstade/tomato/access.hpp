#ifndef PSTADE_TOMATO_ACCESS_HPP
#define PSTADE_TOMATO_ACCESS_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/gravy/boolean_cast.hpp>
#include <pstade/gravy/sdk/windows.hpp>
#include <pstade/nonconstructible.hpp>


namespace pstade { namespace tomato {


    class access :
        private nonconstructible
    {
    public:
        template< class T > static
        BOOL detail_on_idle(T& x)
        {
            return x.on_idle()|gravy::to_boolean;
        }

        template< class T > static
        BOOL detail_pre_translate_message(T& x, MSG *pMsg)
        {
            return x.pre_translate_message(*pMsg)|gravy::to_boolean;
        }
    };


} } // namespace pstade::tomato


#endif
