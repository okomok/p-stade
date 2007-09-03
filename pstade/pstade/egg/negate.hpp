#ifndef PSTADE_EGG_NEGATE_HPP
#define PSTADE_EGG_NEGATE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/adl_barrier.hpp>
#include <pstade/pod_constant.hpp>
#include "./function.hpp"


namespace pstade { namespace egg {


    namespace negate_detail {


        struct baby
        {
            template<class Myself, class X>
            struct apply
            {
                typedef X type;
            };

            template<class Result, class X>
            Result call(X const& x) const
            {
                return -x;
            }
        };


    } // negate_detail


    typedef function_by_cref<negate_detail::baby> op_negate;

    PSTADE_ADL_BARRIER(negate) { // for 'std'
        PSTADE_POD_CONSTANT((op_negate), negate) = {{}};
    }


} } // namespace pstade::egg


#endif
