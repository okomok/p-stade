#ifndef PSTADE_EGG_DETAIL_IS_PLACEHOLDER_EXPRESSION_HPP
#define PSTADE_EGG_DETAIL_IS_PLACEHOLDER_EXPRESSION_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/lambda.hpp>
#include <boost/type_traits/remove_cv.hpp>


namespace pstade { namespace egg { namespace detail {


    template<class Expr>
    struct is_placeholder_expression :
        boost::mpl::is_lambda_expression<
            typename boost::remove_cv<Expr>::type
        >
    { };


} } } // namespace pstade::egg::detail


#endif
