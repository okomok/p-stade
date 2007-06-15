#ifndef PSTADE_GRAVY_REGISTER_WINDOW_MESSAGE_HPP
#define PSTADE_GRAVY_REGISTER_WINDOW_MESSAGE_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/instance.hpp>
#include "./include/tchar.hpp"
#include "./include/windows.hpp"
#include "./tstringize.hpp"


#define PSTADE_GRAVY_REGISTER_WINDOW_MESSAGE(Name, Msg) \
    PSTADE_INSTANCE( \
        (UINT) const, \
        Name, \
        (pstade::gravy::register_window_message_detail::aux(PSTADE_GRAVY_TSTRINGIZE(Msg))) \
    ) \
/**/


namespace pstade { namespace gravy { namespace register_window_message_detail {


    inline
    UINT aux(TCHAR const *msg)
    {
        UINT u = ::RegisterWindowMessage(msg);
        BOOST_ASSERT(u != 0);
        return u;
    }


} } } // namespace pstade::gravy::register_window_message_detail


#endif
