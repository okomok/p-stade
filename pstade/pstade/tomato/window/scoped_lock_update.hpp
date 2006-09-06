#ifndef PSTADE_TOMATO_WINDOW_SCOPED_LOCK_UPDATE_HPP
#define PSTADE_TOMATO_WINDOW_SCOPED_LOCK_UPDATE_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp>
#include "./window_ref.hpp"


namespace pstade { namespace tomato {


struct scoped_lock_update
{
    explicit scoped_lock_update(window_ref wnd)
    {
        ::LockWindowUpdate(wnd);
    }

    ~scoped_lock_update()
    {
        ::LockWindowUpdate(NULL);
    }
};


} } // namespace pstade::tomato


#endif
