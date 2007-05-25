#ifndef PSTADE_APPLE_IS_HASH_SET_HPP
#define PSTADE_APPLE_IS_HASH_SET_HPP


// PStade.Apple
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] <boost/serialization/hash_set.hpp>


#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include "./hash_set_fwd.hpp"


namespace pstade { namespace apple {


namespace is_hash_set_detail {


    template< class T >
    struct aux :
        boost::mpl::false_
    { };


#if defined(BOOST_HAS_HASH)
    template< class Key, class HashFcn, class EqualKey, class Allocator >
    struct aux< BOOST_STD_EXTENSION_NAMESPACE::hash_set<Key, HashFcn, EqualKey, Allocator> > :
        boost::mpl::true_
    { };
#endif


    template< class T >
    struct aux_multi :
        boost::mpl::false_
    { };


#if defined(BOOST_HAS_HASH)
    template< class Key, class HashFcn, class EqualKey, class Allocator >
    struct aux_multi< BOOST_STD_EXTENSION_NAMESPACE::hash_multiset<Key, HashFcn, EqualKey, Allocator> > :
        boost::mpl::true_
    { };
#endif


} // namespace is_hash_set_detail


template< class T >
struct is_hash_set :
    is_hash_set_detail::aux<
        typename boost::remove_cv<T>::type
    >
{ };


template< class T >
struct is_hash_multiset :
    is_hash_set_detail::aux_multi<
        typename boost::remove_cv<T>::type
    >
{ };


} } // namespace pstade::apple


#endif
