#ifndef PSTADE_EGG_MAKE_FUNCTION_HPP
#define PSTADE_EGG_MAKE_FUNCTION_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./function.hpp"
#include "./function_by_value.hpp"


namespace pstade { namespace egg {


    namespace make_function_detail {


        struct baby
        {
            template<class Myself, class Baby>
            struct apply
            {
                typedef function<Baby> type;
            };

            template<class Result, class Baby>
            Result call(Baby baby) const
            {
                Result r = { baby };
                return r;
            }
        };


    } // namespace make_function_detail


    typedef function_by_value<make_function_detail::baby> op_make_function;
    PSTADE_POD_CONSTANT((op_make_function), make_function) = {{}};


} } // namespace pstade::egg


#endif
