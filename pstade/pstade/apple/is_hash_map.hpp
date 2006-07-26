#ifndef PSTADE_APPLE_IS_HASH_MAP_HPP
#define PSTADE_APPLE_IS_HASH_MAP_HPP


// PStade.Apple
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>
#include <pstade/remove_cvr.hpp>
#include "./hash_map_fwd.hpp"


namespace pstade { namespace apple {


namespace is_hash_map_detail {


    template< class T >
    struct aux :
        boost::mpl::false_
    { };


    template< class Kty, class Tr, class Alloc >
    struct aux< stdext::hash_map< Kty, Tr, Alloc> > :
        boost::mpl::true_
    { };


    template< class T >
    struct aux_multi :
        boost::mpl::false_
    { };


    template< class Kty, class Tr, class Alloc >
    struct aux_multi< stdext::hash_multimap<Kty, Tr, Alloc> > :
        boost::mpl::true_
    { };


} // namespace is_hash_map_detail


template< class T >
struct is_hash_map :
    is_hash_map_detail::aux<
        typename remove_cvr<T>::type
    >
{ };


template< class T >
struct is_hash_multimap :
    is_hash_map_detail::aux_multi<
        typename remove_cvr<T>::type
    >
{ };


} } // namespace pstade::apple


#endif
