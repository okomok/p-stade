#ifndef PSTADE_EGG_STATIC_HPP
#define PSTADE_EGG_STATIC_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/result_of.hpp>
#include "./by_perfect.hpp"
#include "./fuse.hpp"
#include "./variadic.hpp"


namespace pstade { namespace egg {


    namespace static_detail {


        template<class Function>
        struct little
        {
            template<class Myself, class Args>
            struct apply :
                result_of<
                    typename result_of<T_fuse(Function)>::type(Args&)
                >
            { };

            template<class Result, class Args>
            Result call(Args& args) const
            {
                return fuse(Function())(args);
            }
        };


    } // namespace static_detail


    template<class Function, class Strategy = by_perfect>
    struct static_ :
        variadic<static_detail::little<Function>, Strategy, use_nullary_result>
    { };

    #define PSTADE_EGG_STATIC() PSTADE_EGG_VARIADIC_L {} PSTADE_EGG_VARIADIC_R


} } // namespace pstade::egg


#endif
