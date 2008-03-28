#ifndef BOOST_EGG_EXPR_HPP
#define BOOST_EGG_EXPR_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/typeof/typeof.hpp>
#include <boost/egg/mono.hpp>
#include <boost/egg/result_of.hpp>

#if !defined(BOOST_TYPEOF_NATIVE)
    #include <boost/function.hpp>
    #include <boost/egg/detail/boost_function_typeof.hpp>
#endif


namespace boost { namespace egg {


#if !defined(BOOST_TYPEOF_NATIVE)

    // X_mono needed for use_default specified as return type.
    template<class Signature, class Base> inline
    boost::function<typename result_of_<X_mono<Signature>(Base &)>::type::signature_type>
    expr(Base base)
    {
        return base;
    }

#else

    template<class Signature, class Base> inline
    typename result_of_<X_mono<Signature>(Base &)>::type
    expr(Base base)
    {
        return X_mono<Signature>()(base);
    }

#endif


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
