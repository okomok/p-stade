#ifndef PSTADE_APPLE_IS_SET_HPP
#define PSTADE_APPLE_IS_SET_HPP


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


#include <boost/mpl/bool.hpp>
#include <pstade/remove_cvr.hpp>
#include "./set_fwd.hpp"


namespace pstade { namespace apple {


namespace is_set_detail {


    template< class T >
    struct aux :
        boost::mpl::false_
    { };


    template< class Kty, class Pr, class Alloc >
    struct aux< std::set<Kty, Pr, Alloc> > :
        boost::mpl::true_
    { };


    template< class T >
    struct aux_multi :
        boost::mpl::false_
    { };


    template< class Kty, class Pr, class Alloc >
    struct aux_multi< std::multiset<Kty, Pr, Alloc> > :
        boost::mpl::true_
    { };


} // namespace is_set_detail


template< class T >
struct is_set :
    is_set_detail::aux<
        typename remove_cvr<T>::type
    >
{ };


template< class T >
struct is_multiset :
    is_set_detail::aux_multi<
        typename remove_cvr<T>::type
    >
{ };


} } // namespace pstade::apple


#endif
