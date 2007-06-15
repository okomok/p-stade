#ifndef PSTADE_GRAVY_MAIN_INSTANCE_HPP
#define PSTADE_GRAVY_MAIN_INSTANCE_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/instance.hpp>
#include "./handle_cast.hpp"
#include "./include/windows.hpp"


namespace pstade { namespace gravy {


    namespace main_instance_detail {

        inline
        HINSTANCE get()
        {
            HINSTANCE h = gravy::handle_cast<HINSTANCE>(::GetModuleHandle(0));
            BOOST_ASSERT("gravy::main_instance initialization failure" && h != NULL);
            return h;
        }

    }


    PSTADE_INSTANCE((HINSTANCE) const, main_instance, (main_instance_detail::get()))


} } // namespace pstade::gravy


#endif
