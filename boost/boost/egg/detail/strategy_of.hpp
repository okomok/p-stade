#ifndef BOOST_EGG_DETAIL_STRATEGY_OF_HPP
#define BOOST_EGG_DETAIL_STRATEGY_OF_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/remove_cv.hpp>
#include <boost/egg/function_fwd.hpp>


namespace boost { namespace egg { namespace details {


    template<class Function>
    struct strategy_of_aux
    {
        typedef typename Function::strategy_type type;
    };

    // minimize name lookup.
    template<class Little, class Strategy>
    struct strategy_of_aux< function<Little, Strategy> >
    {
        typedef Strategy type;
    };


    template<class Function>
    struct strategy_of :
        strategy_of_aux<typename boost::remove_cv<Function>::type>
    { };


} } } // namespace boost::egg::details


#endif
