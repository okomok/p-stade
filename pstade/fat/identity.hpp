#ifndef PSTADE_FAT_IDENTITY_HPP
#define PSTADE_FAT_IDENTITY_HPP
#include "./detail/prefix.hpp"


// PStade.Fat
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/adl_barrier.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/object.hpp>


namespace pstade { namespace fat {


    namespace identity_detail {


        struct baby
        {
            template<class Myself, class X>
            struct apply
            {
                typedef X& type;
            };

            template<class Result, class X>
            Result call(X& x) const
            {
                return x;
            }
        };


    } // namespace identity_detail


    typedef egg::function<identity_detail::baby> op_identity;
    PSTADE_ADL_BARRIER(identity) { // for 'std'
        PSTADE_EGG_OBJECT((op_identity), identity) = { {} };
    }


} } // namespace pstade::fat


#endif
