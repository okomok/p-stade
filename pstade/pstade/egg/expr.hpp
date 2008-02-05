#ifndef PSTADE_EGG_EXPR_HPP
#define PSTADE_EGG_EXPR_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/typeof/typeof.hpp>
#include <pstade/result_of.hpp>
#include "./mono.hpp"

#if !defined(BOOST_TYPEOF_NATIVE)
    #include <boost/function.hpp>
    #include "./detail/typeof_boost_function.hpp"
#endif


namespace pstade { namespace egg {


#if !defined(BOOST_TYPEOF_NATIVE)

    template<class Signature, class Base> inline
    boost::function<typename result_of<X_mono<Signature>(Base&)>::type::signature_type>
    expr(Base base)
    {
        return base;
    }

#else

    template<class Signature, class Base> inline
    typename result_of<X_mono<Signature>(Base&)>::type
    expr(Base base)
    {
        return X_mono<Signature>()(base);
    }

#endif


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif
