#ifndef PSTADE_EGG_MAKE_FUNCTION_HPP
#define PSTADE_EGG_MAKE_FUNCTION_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./by_perfect.hpp"
#include "./by_value.hpp"


namespace pstade { namespace egg {


    namespace make_function_detail {


        template<class Strategy>
        struct little
        {
            template<class Myself, class Little>
            struct apply
            {
                typedef function<Little, Strategy> type;
            };

            template<class Result, class Little>
            Result call(Little l) const
            {
                Result r = { l };
                return r;
            }
        };


    } // namespace make_function_detail


    template<class Strategy = by_perfect>
    struct X_make_function :
        function<make_function_detail::little<Strategy>, by_value>
    { };


    typedef X_make_function<>::function_type T_make_function;
    PSTADE_POD_CONSTANT((T_make_function), make_function) = {{}};


} } // namespace pstade::egg


#endif
