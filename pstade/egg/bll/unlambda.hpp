#ifndef PSTADE_EGG_BLL_UNLAMBDA_HPP
#define PSTADE_EGG_BLL_UNLAMBDA_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/lambda/core.hpp> // unlambda
#include <pstade/pod_constant.hpp>
#include "../by_value.hpp"
#include "../deduced_form.hpp"


namespace pstade { namespace egg {


    namespace bll_unlambda_detail {


        struct little
        {
            typedef deduced_form call_strategy;

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
            Result call(boost::type<Result>, Function fun) const
            {
                return fun;
            }

            template<class Result, class Arg>
            Result call(boost::type<Result>, boost::lambda::lambda_functor<Arg> lam) const
            {
                return boost::lambda::unlambda(lam);
            }
        };


    } // namespace bll_unlambda


    typedef function<bll_unlambda_detail::little, by_value> T_bll_unlambda;
    PSTADE_POD_CONSTANT((T_bll_unlambda), bll_unlambda) = {{}};


} } // namespace pstade::egg


#endif
