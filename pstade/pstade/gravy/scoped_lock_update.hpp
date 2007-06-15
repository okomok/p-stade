#ifndef PSTADE_GRAVY_SCOPED_LOCK_UPDATE_HPP
#define PSTADE_GRAVY_SCOPED_LOCK_UPDATE_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./sdk/windows.hpp"
#include "./window_ref.hpp"


namespace pstade { namespace gravy {


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


} } // namespace pstade::gravy


#endif
