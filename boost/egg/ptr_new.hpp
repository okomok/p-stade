#ifndef BOOST_EGG_PTR_NEW_HPP
#define BOOST_EGG_PTR_NEW_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/pointee.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/compose.hpp>
#include <boost/egg/construct.hpp>
#include <boost/egg/new.hpp>
#include <boost/egg/register_nullary_result.hpp>


namespace boost { namespace egg {


    template<class Ptr, class Strategy = use_default>
    struct X_ptr_new :
        result_of_compose<
            X_construct<Ptr, by_value>,
            X_new<typename pointee<Ptr>::type, Strategy>,
            Ptr,
            Strategy
        >::type
    { };


} } // namespace boost::egg


BOOST_EGG_REGISTER_NULLARY_RESULT_OF_TEMPLATE(boost::egg::X_ptr_new, (class)(class))


#include <boost/egg/detail/suffix.hpp>
#endif
