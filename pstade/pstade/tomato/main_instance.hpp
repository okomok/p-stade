#ifndef PSTADE_TOMATO_MAIN_INSTANCE_HPP
#define PSTADE_TOMATO_MAIN_INSTANCE_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/instance.hpp>
#include "./handle_cast.hpp"


namespace pstade { namespace tomato {


    namespace main_instance_detail {

        inline
        HINSTANCE get()
        {
            HINSTANCE h = tomato::handle_cast<HINSTANCE>(::GetModuleHandle(0));
            BOOST_ASSERT(h != NULL);
            return h;
        }

    }


    PSTADE_INSTANCE((HINSTANCE) const, main_instance, (main_instance_detail::get()))


} } // namespace pstade::tomato

#endif
