#ifndef PSTADE_EGG_DEREF_HPP
#define PSTADE_EGG_DEREF_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./by_perfect.hpp"
#include "./detail/deref_extension.hpp"


namespace pstade { namespace egg {


    template<class X>
    struct result_of_deref
    {
        typedef typename
            pstade_egg_extension::Dereferenceable<X>::reference
        type;
    };


    namespace deref_detail {


        struct little
        {
            template<class Myself, class X>
            struct apply :
                result_of_deref<X>
            { };

            template<class Result, class X>
            Result call(X& x) const
            {
                return *x;
            }
        };


    } // namespace deref_detail


    typedef function<deref_detail::little, by_perfect> T_deref;
    PSTADE_POD_CONSTANT((T_deref), deref) = {{}};


} } // namespace pstade::egg


#endif
