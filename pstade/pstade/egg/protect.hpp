#ifndef PSTADE_EGG_PROTECT_HPP
#define PSTADE_EGG_PROTECT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This is the same as `always` tagged with bind expression.


#include <boost/mpl/bool.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/pod_constant.hpp>
#include "./always.hpp"
#include "./by_value.hpp"
#include "./is_bind_expression.hpp"
#include "./tagged.hpp"


namespace pstade { namespace egg {


    namespace protect_detail {
        struct tag;
    }

    template<class Expr>
    struct result_of_protect :
        result_of_tagged<
            typename result_of_always<Expr>::type,
            protect_detail::tag
        >
    { };

    #define PSTADE_EGG_PROTECT_L PSTADE_EGG_TAGGED_L PSTADE_EGG_ALWAYS_L
    #define PSTADE_EGG_PROTECT_R PSTADE_EGG_ALWAYS_R PSTADE_EGG_TAGGED_R
    #define PSTADE_EGG_PROTECT(F) PSTADE_EGG_PROTECT_L F PSTADE_EGG_PROTECT_R


    template<class X>
    struct is_bind_expression_base<X, typename enable_if< is_tagged_with<X, protect_detail::tag> >::type> :
        boost::mpl::true_
    { };


    namespace protect_detail {

        struct little
        {
            template<class Myself, class Expr>
            struct apply :
                result_of_protect<Expr>
            { };

            template<class Result, class Expr>
            Result call(Expr f) const
            {
                Result r = PSTADE_EGG_PROTECT(f);
                return r;
            }
        };

    } // namespace protect_detail

    typedef function<protect_detail::little, by_value> T_protect;
    PSTADE_POD_CONSTANT((T_protect), protect) = {{}};


} } // namespace pstade::egg


#endif
