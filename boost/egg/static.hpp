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
#include <boost/egg/detail/little_static.hpp>
#include <boost/egg/result_of.hpp> // inclusion guaranteed


namespace boost { namespace egg {


    namespace static_detail {


        template<class Fun, class Void = void>
        struct fun_
        {
            typedef Fun type;
        };

        template<class ReturnOf>
        struct fun_<ReturnOf, typename ReturnOf::boost_egg_return_of> :
            ReturnOf
        { };

        template<class FunCall>
        struct fun_< result_of<FunCall> > :
            result_of_<FunCall>
        { };

        template<class FunCall>
        struct fun_< result_of_<FunCall> > :
            result_of_<FunCall>
        { };


    } // namespace static_detail


    template<class Fun, class Strategy = by_perfect>
    struct static_
    {
        typedef
            function<
                details::little_static<typename static_detail::fun_<Fun>::type, Strategy>,
                Strategy
            >
        type;
    };

    #define BOOST_EGG_STATIC() {{}}


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
