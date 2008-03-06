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
#include <boost/egg/detail/boost_is_placeholder_fwd.hpp>


#if defined(BOOST_MSVC)
    #pragma warning(push)
    #pragma warning(disable: 4305) // 'specialization' : truncation from 'boost::is_placeholder<T>::_vt' to 'bool'
#endif


namespace boost { namespace egg {


    template<class T>
    struct is_placeholder_ :
        mpl::bool_<is_placeholder<T>::value>
    { };


} } // namespace boost::egg


#if defined(BOOST_MSVC)
    #pragma warning(pop)
#endif


#endif
