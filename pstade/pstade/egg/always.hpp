#ifndef PSTADE_EGG_ALWAYS_HPP
#define PSTADE_EGG_ALWAYS_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./by_cref.hpp"
#include "./generator.hpp"
#include "./use_variadic1.hpp"
#include "./variadic.hpp"


namespace pstade { namespace egg {


    namespace always_detail {


        template<class Value>
        struct little_result
        {
            typedef Value base_type;

            Value m_value;

            Value const& base() const
            {
                return m_value;
            }

            template<class Myself, class Args>
            struct apply
            {
                typedef Value type;
            };

            template<class Result, class Args>
            Result call(Args& ) const
            {
                return m_value;
            }
        };


    } // namespace always_detail


    template<class Value>
    struct result_of_always :
        variadic<always_detail::little_result<Value>, by_cref, use_nullary_result>
    { };

    #define PSTADE_EGG_ALWAYS_L PSTADE_EGG_VARIADIC_L {
    #define PSTADE_EGG_ALWAYS_R } PSTADE_EGG_VARIADIC_R
    #define PSTADE_EGG_ALWAYS(V) PSTADE_EGG_ALWAYS_L V PSTADE_EGG_ALWAYS_R


    typedef
        generator<
            result_of_always< deduce<mpl_1, as_wrapped_ref> >::type,
            by_cref,
            use_variadic1
        >::type
    T_always;

    PSTADE_POD_CONSTANT((T_always), always) = PSTADE_EGG_GENERATOR();


} } // namespace pstade::egg


#endif
