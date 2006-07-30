#ifndef PSTADE_APPLE_IS_ASSOCIATIVE_CONTAINER_HPP
#define PSTADE_APPLE_IS_ASSOCIATIVE_CONTAINER_HPP


// PStade.Apple
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/or.hpp>
#include <pstade/remove_cvr.hpp>
#include "./is_hash_map.hpp"
#include "./is_hash_set.hpp"
#include "./is_map.hpp"
#include "./is_set.hpp"


namespace pstade { namespace apple {


template< class T, class = void >
struct is_associative_container_impl :
    boost::mpl::or_<
        boost::mpl::or_<
            is_map<T>,
            is_multimap<T>,
            is_set<T>,
            is_multiset<T>
        >,
        boost::mpl::or_<
            is_hash_map<T>,
            is_hash_multimap<T>,
            is_hash_set<T>,
            is_hash_multiset<T>
        >
    >
{ };


template< class T >
struct is_associative_container :
    is_associative_container_impl<
        typename remove_cvr<T>::type
    >
{ };


} } // namespace pstade::apple


#endif
