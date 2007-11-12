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


        template<class Strategy>
        struct pod_
        {
            typedef function<baby<Strategy>, by_value> type;
        };


    } // namespace make_function_detail


    template<class Strategy = by_perfect>
    struct X_make_function :
        make_function_detail::pod_<Strategy>::type
    {
        typedef typename make_function_detail::pod_<Strategy>::type pod_type;
    };


    typedef X_make_function<>::pod_type T_make_function;
    PSTADE_POD_CONSTANT((T_make_function), make_function) = {{}};


} } // namespace pstade::egg


#endif
