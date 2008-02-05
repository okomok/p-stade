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


#include <pstade/derived_from.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./by_value.hpp"
#include "./construct_variadic1.hpp"
#include "./fuse.hpp"
#include "./generator.hpp"
#include "./variadic.hpp"


namespace pstade { namespace egg {


    namespace after_detail {


        template<class Function, class Thunk>
        struct little_result
        {
            Function m_fun;
            Thunk m_thunk;

            template<class Me, class Args>
            struct apply :
                result_of<
                    typename result_of<T_fuse(Function const&)>::type(Args&)
                >
            { };

            template<class Re, class Args>
            Re call(Args& args) const
            {
                Re r = fuse(m_fun)(args);
                m_thunk();
                return r;
            }
        };


    } // namespace after_detail


    template<class Function, class Thunk, class Strategy = boost::use_default>
    struct result_of_after :
        variadic<
            after_detail::little_result<Function, Thunk>,
            Strategy,
            boost::use_default,
            use_nullary_result
        >
    { };

    #define PSTADE_EGG_AFTER_L PSTADE_EGG_VARIADIC_L {
    #define PSTADE_EGG_AFTER_R } PSTADE_EGG_VARIADIC_R
    #define PSTADE_EGG_AFTER(F, T) PSTADE_EGG_AFTER_L F , T PSTADE_EGG_AFTER_R


    template<class Strategy = boost::use_default>
    struct X_after : derived_from_eval<
        generator<
            typename result_of_after<deduce<mpl_1, as_value>, deduce<mpl_2, as_value>, Strategy>::type,
            by_value,
            X_construct_variadic1<>
        >
    >
    { };

    typedef X_after<>::base_class T_after;
    PSTADE_POD_CONSTANT((T_after), after) = PSTADE_EGG_GENERATOR();


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif
