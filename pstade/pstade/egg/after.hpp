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
#include "./by_cref.hpp"
#include "./by_value.hpp"
#include "./fuse.hpp"
#include "./unfuse.hpp"


namespace pstade { namespace egg {


    namespace after_detail {


        template<class Function, class Thunk>
        struct little_fused_result
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
        result_of_unfuse<
            function<after_detail::little_fused_result<Function, Thunk>, by_cref>,
            boost::use_default,
            use_nullary_result,
            Strategy
        >
    { };


    // PSTADE_EGG_UNFUSE_L { { F, T } } PSTADE_EGG_UNFUSE_M PSTADE_EGG_UNFUSE_DEFAULT_PACK PSTADE_EGG_UNFUSE_R
    #define PSTADE_EGG_AFTER_L PSTADE_EGG_UNFUSE_L { {
    #define PSTADE_EGG_AFTER_M ,
    #define PSTADE_EGG_AFTER_R } } PSTADE_EGG_UNFUSE_M PSTADE_EGG_UNFUSE_DEFAULT_PACK PSTADE_EGG_UNFUSE_R
    #define PSTADE_EGG_AFTER(F, T) PSTADE_EGG_AFTER_L F PSTADE_EGG_AFTER_M T PSTADE_EGG_AFTER_R


    namespace after_detail {


        template<class Strategy>
        struct little
        {
            template<class Myself, class Function, class Thunk>
            struct apply :
                result_of_after<Function, Thunk, Strategy>
            { };

            template<class Result, class Function, class Thunk>
            Result call(Function f, Thunk t) const
            {
                Result r = PSTADE_EGG_AFTER(f, t);
                return r;
            }
        };


    } // namespace after_detail


    template<class Strategy = boost::use_default>
    struct X_after :
        function<after_detail::little<Strategy>, by_value>
    { };

    typedef X_after<>::function_type T_after;
    PSTADE_POD_CONSTANT((T_after), after) = {{}};


} } // namespace pstade::egg


#endif
