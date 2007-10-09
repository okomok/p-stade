#ifndef PSTADE_EGG_BEFORE_HPP
#define PSTADE_EGG_BEFORE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
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


    namespace before_detail {


        template<class Thunk, class Function>
        struct baby_fused_result
        {
            Thunk m_thunk;
            Function m_fun;

            template<class Myself, class ArgTuple>
            struct apply :
                result_of<
                    typename result_of<T_fuse(Function const&)>::type(ArgTuple&)
                >
            { };

            template<class Result, class ArgTuple>
            Result call(ArgTuple& args) const
            {
                m_thunk();
                return fuse(m_fun)(args);
            }
        };


    } // namespace before_detail


    template<class Thunk, class Function, class Strategy = boost::use_default>
    struct result_of_before :
        result_of_unfuse<
            function<before_detail::baby_fused_result<Thunk, Function>, by_cref>,
            boost::use_default,
            use_nullary_result,
            Strategy
        >
    { };


    // PSTADE_EGG_UNFUSE_L { { T, F } } PSTADE_EGG_UNFUSE_M PSTADE_EGG_UNFUSE_DEFAULT_PACK PSTADE_EGG_UNFUSE_R
    #define PSTADE_EGG_BEFORE_L PSTADE_EGG_UNFUSE_L { {
    #define PSTADE_EGG_BEFORE_M ,
    #define PSTADE_EGG_BEFORE_R } } PSTADE_EGG_UNFUSE_M PSTADE_EGG_UNFUSE_DEFAULT_PACK PSTADE_EGG_UNFUSE_R


    namespace before_detail {


        struct baby
        {
            template<class Myself, class Thunk, class Function>
            struct apply :
                result_of_before<Thunk, Function>
            { };

            template<class Result, class Thunk, class Function>
            Result call(Thunk t, Function f) const
            {
                Result r = PSTADE_EGG_BEFORE_L t PSTADE_EGG_BEFORE_M f PSTADE_EGG_BEFORE_R;
                return r;
            }
        };


    } // namespace before_detail


    typedef function<before_detail::baby, by_value> T_before;
    PSTADE_POD_CONSTANT((T_before), before) = {{}};


} } // namespace pstade::egg


#endif
