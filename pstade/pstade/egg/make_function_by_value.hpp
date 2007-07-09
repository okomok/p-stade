#ifndef PSTADE_EGG_MAKE_FUNCTION_BY_VALUE_HPP
#define PSTADE_EGG_MAKE_FUNCTION_BY_VALUE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./function_by_value.hpp"


namespace pstade { namespace egg {


    namespace make_function_by_value_detail {


        struct baby
        {
            template<class Myself, class Baby>
            struct apply
            {
                typedef function_by_value<Baby> type;
            };

            template<class Result, class Baby>
            Result call(Baby baby) const
            {
                Result r = { baby };
                return r;
            }
        };


    } // namespace make_function_by_value_detail


    typedef function_by_value<make_function_by_value_detail::baby> op_make_function_by_value;
    PSTADE_POD_CONSTANT((op_make_function_by_value), make_function_by_value) = {{}};


} } // namespace pstade::egg


#endif
