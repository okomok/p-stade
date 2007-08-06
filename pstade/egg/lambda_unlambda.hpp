#ifndef PSTADE_EGG_LAMBDA_UNLAMBDA_HPP
#define PSTADE_EGG_LAMBDA_UNLAMBDA_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/lambda/core.hpp> // unlambda
#include <boost/type.hpp>
#include <pstade/pod_constant.hpp>
#include "./function_by_value.hpp"


namespace pstade { namespace egg {


    namespace lambda_unlambda_detail {


        struct baby
        {
            template<class Myself, class Function>
            struct apply
            {
                typedef Function type;
            };

            template<class Myself, class Arg>
            struct apply< Myself, boost::lambda::lambda_functor<Arg> >
            {
                typedef boost::lambda::non_lambda_functor< boost::lambda::lambda_functor<Arg> > type;
            };

            template<class Result, class Function>
            Result call(Function fun) const
            {
                // "type2type" helps gcc-3.4 to overload.
                return call_aux(boost::type<Result>(), fun);
            }

            template<class Result, class Function>
            Result call_aux(boost::type<Result>, Function fun) const
            {
                return fun;
            }

            template<class Result, class Arg>
            Result call_aux(boost::type<Result>, boost::lambda::lambda_functor<Arg> lam) const
            {
                return boost::lambda::unlambda(lam);
            }
        };


    } // namespace lambda_unlambda


    typedef function_by_value<lambda_unlambda_detail::baby> op_lambda_unlambda;
    PSTADE_POD_CONSTANT((op_lambda_unlambda), lambda_unlambda) = {{}};


} } // namespace pstade::egg


#endif
