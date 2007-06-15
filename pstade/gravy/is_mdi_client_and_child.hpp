#ifndef PSTADE_GRAVY_IS_MDI_CLIENT_AND_CHILD_HPP
#define PSTADE_GRAVY_IS_MDI_CLIENT_AND_CHILD_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/constant.hpp>
#include "./is_owned.hpp"
#include "./is_parent_of.hpp"
#include "./window_ref.hpp"


namespace pstade { namespace gravy {


    struct op_is_mdi_client_and_child
    {
        typedef bool result_type;

        bool operator()(window_ref mdiClient, window_ref child) const
       {
            return !is_owned(child) && is_parent_of(mdiClient, child);
        }
    };


    PSTADE_CONSTANT(is_mdi_client_and_child, (op_is_mdi_client_and_child))


} } // namespace pstade::gravy


#endif
