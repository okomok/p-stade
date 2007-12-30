#ifndef PSTADE_EGG_DETAIL_APPLY_IF_BIND_EXPR_HPP
#define PSTADE_EGG_DETAIL_APPLY_IF_BIND_EXPR_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/pod_constant.hpp>
#include "../always.hpp"
#include "../by_cref.hpp"
#include "../is_bind_expression.hpp"


namespace pstade { namespace egg { namespace detail {


    struct baby_apply_if_bind_expr
    {
        template<class Myself, class X>
        struct apply :
            boost::mpl::eval_if< is_bind_expression<X>,
                boost::remove_cv<X>, // strip reference, so that used in result_of<X(...)>.
                result_of<T_always(X&)>
            >
        { };

        template<class Result, class X>
        Result call(X& x, typename enable_if< is_bind_expression<X> >::type = 0) const
        {
            return x;
        }

        template<class Result, class X>
        Result call(X& x, typename disable_if<is_bind_expression<X> >::type = 0) const
        {
            // TODO: always should support boost::ref?
            return always(x);
        }                
    };


    typedef function<baby_apply_if_bind_expr, by_cref> T_apply_if_bind_expr;
    PSTADE_POD_CONSTANT((T_apply_if_bind_expr), apply_if_bind_expr) = {{}};


} } } // namespace pstade::egg::detail


#endif
