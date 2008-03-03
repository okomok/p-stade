#ifndef BOOST_EGG_BLL_UNLAMBDA_HPP
#define BOOST_EGG_BLL_UNLAMBDA_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/lambda/core.hpp> // unlambda
#include <boost/egg/by_value.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/use_deduced_form.hpp>
#include <boost/egg/bll/result_of.hpp> // inclusion guaranteed


namespace boost { namespace egg {


    namespace bll_unlambda_detail {


        struct little
        {
            typedef void use_deduced_form;

            template<class Me, class Function>
            struct apply
            {
                typedef Function type;
            };

            template<class Me, class Arg>
            struct apply< Me, lambda::lambda_functor<Arg> >
            {
                typedef lambda::non_lambda_functor< lambda::lambda_functor<Arg> > type;
            };

            template<class Re, class Function>
            Re call(boost::type<Re>, Function fun) const
            {
                return fun;
            }

            template<class Re, class Arg>
            Re call(boost::type<Re>, lambda::lambda_functor<Arg> lam) const
            {
                return lambda::unlambda(lam);
            }
        };


    } // namespace bll_unlambda


    typedef function<bll_unlambda_detail::little, by_value> T_bll_unlambda;
    BOOST_EGG_CONST((T_bll_unlambda), bll_unlambda) = {{}};


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
