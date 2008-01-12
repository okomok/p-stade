#ifndef BOOST_EGG_BEFORE_HPP
#define BOOST_EGG_BEFORE_HPP
#include "./detail/prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.cc.gatech.edu/~yannis/fc++/


#include <boost/egg/pstade/pod_constant.hpp>
#include <boost/egg/pstade/result_of.hpp>
#include "./by_cref.hpp"
#include "./by_value.hpp"
#include "./fuse.hpp"
#include "./unfuse.hpp"


namespace pstade { namespace egg {


    namespace before_detail {


        template<class Thunk, class Function>
        struct little_fused_result
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
            function<before_detail::little_fused_result<Thunk, Function>, by_cref>,
            boost::use_default,
            use_nullary_result,
            Strategy
        >
    { };


    // BOOST_EGG_UNFUSE_L { { T, F } } BOOST_EGG_UNFUSE_M BOOST_EGG_UNFUSE_DEFAULT_PACK BOOST_EGG_UNFUSE_R
    #define BOOST_EGG_BEFORE_L BOOST_EGG_UNFUSE_L { {
    #define BOOST_EGG_BEFORE_M ,
    #define BOOST_EGG_BEFORE_R } } BOOST_EGG_UNFUSE_M BOOST_EGG_UNFUSE_DEFAULT_PACK BOOST_EGG_UNFUSE_R
    #define BOOST_EGG_BEFORE(T, F) BOOST_EGG_BEFORE_L T BOOST_EGG_BEFORE_M F BOOST_EGG_BEFORE_R


    namespace before_detail {


        template<class Strategy>
        struct little
        {
            template<class Myself, class Thunk, class Function>
            struct apply :
                result_of_before<Thunk, Function>
            { };

            template<class Result, class Thunk, class Function>
            Result call(Thunk t, Function f) const
            {
                Result r = BOOST_EGG_BEFORE(t, f);
                return r;
            }
        };


    } // namespace before_detail


    template<class Strategy = boost::use_default>
    struct X_before :
        function<before_detail::little<Strategy>, by_value>
    { };

    typedef X_before<>::function_type T_before;
    PSTADE_POD_CONSTANT((T_before), before) = {{}};


} } // namespace pstade::egg


#endif
