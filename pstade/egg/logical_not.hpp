#ifndef PSTADE_EGG_LOGICAL_NOT_HPP
#define PSTADE_EGG_LOGICAL_NOT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/adl_barrier.hpp>
#include <pstade/make_bool.hpp>
#include <pstade/pod_constant.hpp>


namespace pstade { namespace egg {


    struct T_logical_not
    {
        typedef bool result_type;

        template<class X>
        bool operator()(X const& x) const
        {
            return !make_bool(x);
        }
    };


    PSTADE_ADL_BARRIER(logical_not) {
        PSTADE_POD_CONSTANT((T_logical_not), logical_not) = {};
    }


} } // namespace pstade::egg


#endif
