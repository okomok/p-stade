#ifndef BOOST_EGG_DETAIL_IS_PLACEHOLDER_HPP
#define BOOST_EGG_DETAIL_IS_PLACEHOLDER_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // BOOST_MSVC
#include <boost/mpl/bool.hpp>
#include <boost/version.hpp>

#if BOOST_VERSION >= 103500
    #include <boost/is_placeholder.hpp>
#else
    #include <boost/lambda/core.hpp>
#endif


namespace boost { namespace egg {


#if BOOST_VERSION >= 103500


#if defined(BOOST_MSVC)
    #pragma warning(push)
    #pragma warning(disable: 4305) // 'specialization' : truncation from 'boost::is_placeholder<T>::_vt' to 'bool'
#endif

    template<class T>
    struct is_placeholder_ :
        mpl::bool_<is_placeholder<T>::value>
    { };

#if defined(BOOST_MSVC)
    #pragma warning(pop)
#endif


#else


    template<class T>
    struct is_placeholder_ :
        mpl::false_
    { };


    template< >
    struct is_placeholder_< lambda::lambda_functor< lambda::placeholder<lambda::FIRST> > > :
        mpl::true_
    { };

    template< >
    struct is_placeholder_< lambda::lambda_functor< lambda::placeholder<lambda::SECOND> > > :
        mpl::true_
    { };

    template< >
    struct is_placeholder_< lambda::lambda_functor< lambda::placeholder<lambda::THIRD> > > :
        mpl::true_
    { };


#endif // BOOST_VERSION >= 103500


} } // namespace boost::egg


#endif
