#ifndef BOOST_EGG_RETURN_HPP
#define BOOST_EGG_RETURN_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/by_perfect.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/construct_braced2.hpp>
#include <boost/egg/detail/derived_from.hpp>
#include <boost/egg/detail/little_return_result.hpp>
#include <boost/egg/generator.hpp>
#include <boost/egg/result_of.hpp>


namespace boost { namespace egg {


    template<
        class Base,
        class Return   = use_default,
        class Strategy = by_perfect,
        class Tag      = use_default
    >
    struct result_of_return
    {
        typedef
            function<details::little_return_result<Base, Return, Strategy, Tag>, Strategy>
        type;
    };

    #define BOOST_EGG_RETURN_L { {
    #define BOOST_EGG_RETURN_R } }
    #define BOOST_EGG_RETURN(F) BOOST_EGG_RETURN_L F BOOST_EGG_RETURN_R


    template<
        class Return   = use_default,
        class Strategy = by_perfect,
        class Tag      = use_default
    >
    struct X_return : details::derived_from_eval<
        generator<
            typename result_of_return<deduce<mpl::_1, as_value>, Return, Strategy, Tag>::type,
            by_value,
            X_construct_braced2<>
        > >
    { };

    #define BOOST_EGG_RETURN_INIT BOOST_EGG_GENERATOR()


    template<class Return, class Base> inline
    typename result_of<X_return<Return>(Base &)>::type return_(Base base)
    {
        return X_return<Return>()(base);
    }


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
