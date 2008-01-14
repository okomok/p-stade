#ifndef PSTADE_APPLE_IS_MAP_HPP
#define PSTADE_APPLE_IS_MAP_HPP


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
#include "./map_fwd.hpp"


namespace pstade { namespace apple {


template< class T >
struct is_map :
    boost::mpl::false_
{ };


template< class Kty, class Ty, class Pr, class Alloc >
struct is_map< std::map<Kty, Ty, Pr, Alloc> > :
    boost::mpl::true_
{ };


template< class T >
struct is_multimap :
    boost::mpl::false_
{ };


template< class Kty, class Ty, class Pr, class Alloc >
struct is_multimap< std::multimap< Kty, Ty, Pr, Alloc> > :
    boost::mpl::true_
{ };


} } // namespace pstade::apple


#endif
