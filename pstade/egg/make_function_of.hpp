#ifndef PSTADE_EGG_MAKE_FUNCTION_OF_HPP
#define PSTADE_EGG_MAKE_FUNCTION_OF_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./by_value.hpp"
#include "./function_of.hpp"


namespace pstade { namespace egg {


    namespace make_function_of_detail {


        struct little
        {
            template<class Myself, class Little>
            struct apply :
                function_of<Little>
            { };

            template<class Result, class Little>
            Result call(Little b) const
            {
                Result r = { b };
                return r;
            }
        };


    } // namespace make_function_of_detail


    typedef function<make_function_of_detail::little, by_value> T_make_function_of;
    PSTADE_POD_CONSTANT((T_make_function_of), make_function_of) = {{}};


} } // namespace pstade::egg


#endif
