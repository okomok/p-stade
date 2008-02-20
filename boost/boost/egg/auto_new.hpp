#ifndef BOOST_EGG_AUTO_NEW_HPP
#define BOOST_EGG_AUTO_NEW_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <memory> // auto_ptr
#include <boost/egg/detail/perfect_arities.hpp>
#include <boost/egg/explicit.hpp>
#include <boost/egg/ptr_new.hpp>
#include <boost/egg/register_nullary_result.hpp>


namespace boost { namespace egg {


    template<class T, class Strategy = use_default>
    struct X_auto_new :
        X_ptr_new<std::auto_ptr<T>, Strategy>
    { };

    #define  BOOST_EGG_EXPLICIT_PARAMS (auto_new, X_auto_new, (class), BOOST_EGG_PERFECT_ARITIES())
    #include BOOST_EGG_EXPLICIT()


} } // namespace boost::egg


BOOST_EGG_REGISTER_NULLARY_RESULT_OF_TEMPLATE(boost::egg::X_auto_new, (class)(class))


#include <boost/egg/detail/suffix.hpp>
#endif
