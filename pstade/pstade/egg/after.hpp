#ifndef PSTADE_EGG_AFTER_HPP
#define PSTADE_EGG_AFTER_HPP
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


#include <boost/preprocessor/facilities/identity.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./function.hpp"
#include "./function_by_value.hpp"
#include "./fuse.hpp"
#include "./unfuse.hpp"


namespace pstade { namespace egg {


    namespace after_detail {


        template<class Function, class Thunk>
        struct baby_fused_result
        {
            Function m_fun;
            Thunk m_thunk;

            template<class Myself, class ArgTuple>
            struct apply :
                result_of<
                    typename result_of<op_fuse(Function const&)>::type(ArgTuple&)
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


    template<class Function, class Thunk>
    struct result_of_after :
        result_of_unfuse<
            function< after_detail::baby_fused_result<Function, Thunk> >,
            boost::use_default,
            use_nullary_result
        >
    { }; // ::type = { { { { Function, Thunk } }, {} } };


    #define PSTADE_EGG_AFTER_RESULT_INITIALIZER(F, T) \
        { { { { F(), T() } }, {} } } \
    /**/


    namespace after_detail {


        struct baby
        {
            template<class Myself, class Function, class Thunk>
            struct apply :
                result_of_after<Function, Thunk>
            { };

            template<class Result, class Function, class Thunk>
            Result call(Function f, Thunk t) const
            {
                Result r = PSTADE_EGG_AFTER_RESULT_INITIALIZER(BOOST_PP_IDENTITY(f), BOOST_PP_IDENTITY(t));
                return r;
            }
        };


    } // namespace after_detail


    typedef egg::function_by_value<after_detail::baby> op_after;
    PSTADE_POD_CONSTANT((op_after), after) = {{}};


} } // namespace pstade::egg


#endif
