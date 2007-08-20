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


#include <boost/preprocessor/facilities/empty.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./function.hpp"
#include "./function_by_value.hpp"
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
                    typename result_of<op_fuse(Function const&)>::type(ArgTuple&)
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


    template<class Thunk, class Function>
    struct result_of_before :
        result_of_unfuse<
            function< before_detail::baby_fused_result<Thunk, Function> >,
            boost::use_default,
            use_nullary_result
        >
    { }; // ::type = { { { { Thunk, Function } }, {} } };


    #define PSTADE_EGG_BEFORE(T, F) \
        { { { { T(), F() } }, {} } } BOOST_PP_EMPTY \
    /**/


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
                Result r = PSTADE_EGG_BEFORE(t BOOST_PP_EMPTY, f BOOST_PP_EMPTY)();
                return r;
            }
        };


    } // namespace before_detail


    typedef egg::function_by_value<before_detail::baby> op_before;
    PSTADE_POD_CONSTANT((op_before), before) = {{}};


} } // namespace pstade::egg


#endif
