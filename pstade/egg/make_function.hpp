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
#include "./by_perfect.hpp"
#include "./by_value.hpp"


namespace pstade { namespace egg {


    namespace make_function_detail {


        template<class Strategy>
        struct baby
        {
            template<class Myself, class Baby>
            struct apply
            {
                typedef function<Baby, Strategy> type;
            };

            template<class Result, class Baby>
            Result call(Baby b) const
            {
                Result r = { b };
                return r;
            }
        };


    } // namespace make_function_detail


    template<class Strategy = by_perfect>
    struct tp_make_function
    {
        typedef
            function<make_function_detail::baby<Strategy>, by_value>
        type;
    };


    template<class Strategy = by_perfect>
    struct X_make_function :
        tp_make_function<Strategy>::type
    { };


    typedef tp_make_function<>::type T_make_function;
    PSTADE_POD_CONSTANT((T_make_function), make_function) = {{}};


} } // namespace pstade::egg


#endif
