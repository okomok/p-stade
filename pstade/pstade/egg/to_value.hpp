#ifndef PSTADE_EGG_TO_VALUE_HPP
#define PSTADE_EGG_TO_VALUE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./ambi.hpp"
#include "./by_value.hpp"


namespace pstade { namespace egg {


    namespace to_value_detail {


        struct little
        {
            template<class Me, class A>
            struct apply
            {
                typedef A type;
            };

            template<class Re, class A>
            Re call(A a) const
            {
                return a;
            }
        };


    } // namespace to_value_detail


    typedef result_of_ambi0<function<to_value_detail::little, by_value>, by_value>::type T_to_value;
    PSTADE_POD_CONSTANT((T_to_value), to_value) = PSTADE_EGG_AMBI({{}});


} } // namespace pstade::egg


#endif
