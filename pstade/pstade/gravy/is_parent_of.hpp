#ifndef PSTADE_GRAVY_IS_PARENT_OF_HPP
#define PSTADE_GRAVY_IS_PARENT_OF_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// ::IsChild


#include <pstade/pod_constant.hpp>
#include "./sdk/windows.hpp"
#include "./window_ref.hpp"


namespace pstade { namespace gravy {


    struct op_is_parent_of
    {
        typedef bool result_type;

        bool operator()(window_ref parent, window_ref child) const
        {
            return parent == ::GetParent(child);
        }
    };


    PSTADE_POD_CONSTANT((op_is_parent_of), is_parent_of) = {};


} } // namespace pstade::gravy


#endif
