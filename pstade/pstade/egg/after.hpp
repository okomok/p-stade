#ifndef PSTADE_EGG_AFTER_HPP
#define PSTADE_EGG_AFTER_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.cc.gatech.edu/~yannis/fc++/


#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./by_value.hpp"
#include "./fuse.hpp"
#include "./generator.hpp"
#include "./use_variadic1.hpp"
#include "./variadic.hpp"


namespace pstade { namespace egg {


    namespace after_detail {


        template<class Function, class Thunk>
        struct little_result
        {
            Function m_fun;
            Thunk m_thunk;

            template<class Myself, class ArgTuple>
            struct apply :
                result_of<
                    typename result_of<T_fuse(Function const&)>::type(ArgTuple&)
                >
            { };

            template<class Result, class ArgTuple>
            Result call(ArgTuple& args) const
            {
                Result r = fuse(m_fun)(args);
                m_thunk();
                return r;
            }
        };


    } // namespace after_detail


    template<class Function, class Thunk, class Strategy = boost::use_default>
    struct result_of_after :
        variadic<after_detail::little_result<Function, Thunk>, Strategy, use_nullary_result>
    { };

    #define PSTADE_EGG_AFTER_L PSTADE_EGG_VARIADIC_L {
    #define PSTADE_EGG_AFTER_M ,
    #define PSTADE_EGG_AFTER_R } PSTADE_EGG_VARIADIC_R
    #define PSTADE_EGG_AFTER(F, T) PSTADE_EGG_AFTER_L F PSTADE_EGG_AFTER_M T PSTADE_EGG_AFTER_R


    template<class Strategy = boost::use_default>
    struct X_after :
        generator<
            typename result_of_after<deduce<mpl_1, as_value>, deduce<mpl_2, as_value>, Strategy>::type,
            by_value,
            use_variadic1
        >::type
    { };

    typedef X_after<>::function_type T_after;
    PSTADE_POD_CONSTANT((T_after), after) = PSTADE_EGG_GENERATOR();


} } // namespace pstade::egg


#endif
