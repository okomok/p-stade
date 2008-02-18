#ifndef BOOST_EGG_BY_PERFECT_HPP
#define BOOST_EGG_BY_PERFECT_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/bytag_at.hpp>
#include <boost/egg/detail/perfect_arities.hpp>
#include <boost/egg/detail/result_of_forward.hpp>
#include <boost/egg/function_fwd.hpp> // by_perfect
#include <boost/egg/perfect_strategy.hpp>


namespace boost { namespace egg {


    namespace details {


        template<int Arity, int Index>
        struct bytag_at<by_perfect, Arity, Index>
        {
            typedef by_perfect type;
        };

        template<int Arity, int Index>
        struct bytag_at<by_perfect const, Arity, Index>
        {
            typedef by_perfect type;
        };


    } // namespace details


    template<class Lvalue>
    struct result_of_forward<by_perfect, Lvalue>
    {
        typedef Lvalue &type;
    };


} } // namespace boost::egg


#define  BOOST_EGG_PERFECT_STRATEGY_PARAMS (boost::egg::by_perfect, BOOST_EGG_PERFECT_ARITIES())
#include BOOST_EGG_PERFECT_STRATEGY()


#include <boost/egg/detail/suffix.hpp>
#endif
