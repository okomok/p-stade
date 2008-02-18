#ifndef BOOST_EGG_DETAIL_IS_PLACEHOLDER_EXPRESSION_HPP
#define BOOST_EGG_DETAIL_IS_PLACEHOLDER_EXPRESSION_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/lambda.hpp>
#include <boost/type_traits/remove_cv.hpp>


namespace boost { namespace egg { namespace details {


    template<class Expr>
    struct is_placeholder_expression :
        mpl::is_lambda_expression<
            typename boost::remove_cv<Expr>::type
        >
    { };


} } } // namespace boost::egg::details


#endif
