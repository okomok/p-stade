#ifndef PSTADE_TO_REF_HPP
#define PSTADE_TO_REF_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/auxiliary.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/provide_sig.hpp>


namespace pstade {


    namespace to_ref_detail {


        struct op :
            callable<op>
        {
            template< class Myself, class X >
            struct apply
            {
                typedef X& type;
            };

            template< class Result, class X >
            Result call(X& x) const
            {
                return x;
            }
        };


        struct op_c :
            callable<op_c>
        {
            template< class Myself, class X >
            struct apply
            {
                typedef X const& type;
            };

            template< class Result, class X >
            Result call(X const& x) const
            {
                return x;
            }
        };


    } // namespace to_ref_detail


    PSTADE_AUXILIARY(0, to_ref,  (to_ref_detail::op))
    PSTADE_AUXILIARY(0, to_cref, (to_ref_detail::op_c))


} // namespace pstade


#endif
