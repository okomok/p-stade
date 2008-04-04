#ifndef BOOST_EGG_STATIC_HPP
#define BOOST_EGG_STATIC_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/by_perfect.hpp>
#include <boost/egg/detail/boost_result_of_fwd.hpp>
#include <boost/egg/detail/egg_result_of_fwd.hpp>
#include <boost/egg/detail/little_static.hpp>
#include <boost/egg/result_of.hpp>


namespace boost { namespace egg {


    template<class Fun, class Strategy = by_perfect>
    struct static_
    {
        typedef
            function<
                details::little_static<Fun, Strategy>,
                Strategy
            >
        type;
    };

    #define BOOST_EGG_STATIC() {{}}


    template<class FunCall, class Strategy>
    struct static_<result_of<FunCall>, Strategy> :
        static_<typename result_of<FunCall>::type, Strategy>
    { };

    template<class FunCall, class Strategy>
    struct static_<result_of_<FunCall>, Strategy> :
        static_<typename result_of_<FunCall>::type, Strategy>
    { };


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
